#include "Player.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Player::_bind_methods() {
        ClassDB::bind_method(D_METHOD("attack_animation_finished"), &Player::attack_animation_finished);
        ClassDB::bind_method(D_METHOD("roll_animation_finished"), &Player::roll_animation_finished);
    }

    void Player::_ready(){

        animationPlayer = get_node<AnimationPlayer>("AnimationPlayer");
        animationTree = get_node<AnimationTree>("AnimationTree");
        
        animationState = Object::cast_to<AnimationState>(
            animationTree->get("parameters/playback").operator Object*()
        );

        animationTree->set_active(true);

        set_process(true); // Ensure _process is called each frame
    }

    void Player::_process(double delta) {
        switch (state)
        {
        case MOVE:
            move_state(delta);
            break;
        case ROLL:
            roll_state(delta);
            break;
        case ATTACK:
            attack_state(delta);
        default:
            break;
        }
    }

    void Player::move_state(double delta){
        Vector2 input_vector = Vector2();

        input_vector.x = Input::get_singleton()->get_action_strength("ui_right") - Input::get_singleton()->get_action_strength("ui_left");
        input_vector.y = Input::get_singleton()->get_action_strength("ui_down") - Input::get_singleton()->get_action_strength("ui_up");

        //Standardised the velocity
        input_vector = input_vector.normalized();

        //Multiply by delta if somnething has to change overtime
        if(input_vector != Vector2()){

            // //Player Animation for Right & Left
            // if(input_vector.x > 0){
            //     animationPlayer->play("RunRight");
            // }
            // else{
            //     animationPlayer->play("RunLeft");
            // }
            
            roll_vector = input_vector;

            //Set blend position for idle & run & attack (which position the player is pointing)
            animationTree->set("parameters/Idle/blend_position", input_vector);
            animationTree->set("parameters/Run/blend_position", input_vector);
            animationTree->set("parameters/Attack/blend_position", input_vector);
            animationTree->set("parameters/Roll/blend_position", input_vector);

            animationState->travel("Run");

            velocity = velocity.move_toward(input_vector * MAX_SPEED, ACCELERATION * delta);
        }
        else{
            animationState->travel("Idle");
            velocity = velocity.move_toward(Vector2(), FRICTION * delta);
        }

        move();

        if (InputMap::get_singleton()->has_action("roll") && Input::get_singleton()->is_action_just_pressed("roll")) {
            state = ROLL;
        }

        if (InputMap::get_singleton()->has_action("attack") && Input::get_singleton()->is_action_just_pressed("attack")) {
            state = ATTACK;
        }
    }

    void Player::attack_state(double delta){
        //UtilityFunctions::print("Now Attacking");

        //reset velocity to prevent sliding after attack
        velocity = Vector2();
        animationState->travel("Attack");
    }

    void Player::roll_state(double delta){
        velocity = roll_vector * ROLL_SPEED;
        animationState -> travel("Roll");
        move();
    }

    void Player::move(){
        set_velocity(velocity);
        move_and_slide();
    }

    void Player::attack_animation_finished(){
        //UtilityFunctions::print("Attack animation finished called!");
        state = MOVE;
    }

    void Player::roll_animation_finished(){
        velocity = velocity * 0.8;
        state = MOVE;
    }
}
