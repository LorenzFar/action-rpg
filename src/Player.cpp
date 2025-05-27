#include "Player.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Player::_bind_methods() {
    }

    void Player::_ready(){
        animationPlayer = get_node<AnimationPlayer>("AnimationPlayer");
    }

    void Player::_physics_process(double delta) {
        Vector2 input_vector = Vector2();

        input_vector.x = Input::get_singleton()->get_action_strength("ui_right") - Input::get_singleton()->get_action_strength("ui_left");
        input_vector.y = Input::get_singleton()->get_action_strength("ui_down") - Input::get_singleton()->get_action_strength("ui_up");

        //Standardised the velocity
        input_vector = input_vector.normalized();

        //Multiply by delta if somnething has to change overtime
        if(input_vector != Vector2()){

            //Player Animation for Right & Left
            if(input_vector.x > 0){
                animationPlayer->play("RunRight");
            }
            else{
                animationPlayer->play("RunLeft");
            }

            velocity = velocity.move_toward(input_vector * MAX_SPEED, ACCELERATION * delta);
        }
        else{
            animationPlayer->play("IdleRight");
            velocity = velocity.move_toward(Vector2(), FRICTION * delta);
        }

        set_velocity(velocity);
        move_and_slide();
    }
}
