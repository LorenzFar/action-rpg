#include "Player.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Player::_bind_methods() {
    }

    void Player::_ready(){
        animationPlayer = get_node<AnimationPlayer>("AnimationPlayer");
        animationTree = get_node<AnimationTree>("AnimationTree");
        
        animationState = Object::cast_to<AnimationState>(
            animationTree->get("parameters/playback").operator Object*()
        );
    }

    void Player::_physics_process(double delta) {
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

            //Set blend position for idle & run
            animationTree->set("parameters/Idle/blend_position", input_vector);
            animationTree->set("parameters/Run/blend_position", input_vector);

            animationState->travel("Run");

            velocity = velocity.move_toward(input_vector * MAX_SPEED, ACCELERATION * delta);
        }
        else{
            animationState->travel("Idle");
            velocity = velocity.move_toward(Vector2(), FRICTION * delta);
        }

        set_velocity(velocity);
        move_and_slide();
    }
}
