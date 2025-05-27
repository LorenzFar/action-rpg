#include "Player.h"
#include <godot_cpp/classes/input.hpp>

namespace godot {

    void Player::_bind_methods() {
    }

    void Player::_physics_process(double delta) {
        Vector2 input_vector = Vector2();

        input_vector.x = Input::get_singleton()->get_action_strength("ui_right") - Input::get_singleton()->get_action_strength("ui_left");
        input_vector.y = Input::get_singleton()->get_action_strength("ui_down") - Input::get_singleton()->get_action_strength("ui_up");

        //Standardised the velocity
        input_vector = input_vector.normalized();

        //Multiply by delta if somnething has to change overtime
        if(input_vector != Vector2()){
            velocity = velocity.move_toward(input_vector * MAX_SPEED, ACCELERATION * delta);
        }
        else{
            velocity = velocity.move_toward(Vector2(), FRICTION * delta);
        }

        set_velocity(velocity);
        move_and_slide();
    }
}
