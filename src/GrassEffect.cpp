#include "GrassEffect.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void GrassEffect::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_animation_finished"), &GrassEffect::_on_animation_finished);
    }

    void GrassEffect::_ready(){
        animatedSprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");

        animatedSprite->set_frame(0); // Reset to first frame
        animatedSprite -> play("Animation");

        animatedSprite -> connect(
            "animation_finished",
            Callable(this, "_on_animation_finished")
        );

        set_process(true); // Ensure _process is called each frame
    }

    void GrassEffect::_process(double delta){

    }

    void GrassEffect::_on_animation_finished(){
        queue_free();
    }
}
