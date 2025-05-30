#include "Grass.h"

#include <godot_cpp/classes/resource_loader.hpp> 
#include <godot_cpp/classes/packed_scene.hpp> 
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {

    void Grass::_bind_methods() {
    }

    void Grass::_ready(){
        set_process(true); // Ensure _process is called each frame
    }

    void Grass::_process(double delta) {
        if (InputMap::get_singleton()->has_action("attack") && Input::get_singleton()->is_action_just_pressed("attack")) {
            Ref<PackedScene> grassEffectScene = ResourceLoader::get_singleton()->load("res://assets/Effects/grass_effect.tscn");
            if (grassEffectScene.is_null()) {
                UtilityFunctions::print("Failed to load GrassEffect scene.");
                return;
            }

            Node *grassEffectNode = grassEffectScene->instantiate();
            Node2D *grassEffect = Object::cast_to<Node2D>(grassEffectNode);
            if (!grassEffect) {
                UtilityFunctions::print("GrassEffect is not a Node2D.");
                return;
            }

            // Append to current scene
            get_tree()->get_current_scene()->add_child(grassEffect);

            // Position effect at the current grass node's global position
            grassEffect->set_global_position(get_global_position());

            // Remove the current grass node
            queue_free();
        }
    }
}
