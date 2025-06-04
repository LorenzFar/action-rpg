#include "Effect.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Effect::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_animation_finished"), &Effect::_on_animation_finished);
    }

    void Effect::_ready(){

        set_frame(0); // Reset to first frame
        play("Animation");

        connect(
            "animation_finished",
            Callable(this, "_on_animation_finished")
        );

        set_process(true); // Ensure _process is called each frame
    }

    void Effect::_process(double delta){

    }

    void Effect::_on_animation_finished(){
        queue_free();
    }
}
