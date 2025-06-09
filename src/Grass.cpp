#include "Grass.h"

#include <godot_cpp/classes/resource_loader.hpp> 
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp> 
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Grass::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_area_entered", "area"), &Grass::_on_area_entered);
    }

    void Grass::_ready(){
        area2D = get_node<Area2D>("Hurtbox");
        area2D -> connect(
            "area_entered",
            Callable(this, "_on_area_entered")
        );

        set_process(true); // Ensure _process is called each frame
    }

    void Grass::create_grass_effect() {
        Ref<PackedScene> grassEffectScene = ResourceLoader::get_singleton()->load("res://assets/Effects/grass_effect.tscn");
        if (grassEffectScene.is_null()) {
            UtilityFunctions::print("Failed to load GrassEffect scene.");
            return;
        }

        Node *grassEffectNode = grassEffectScene->instantiate();
        AnimatedSprite2D *grassEffect = Object::cast_to<AnimatedSprite2D>(grassEffectNode);
        if (!grassEffect) {
            UtilityFunctions::print("GrassEffect is not a AnimatedSprite2D.");
            return;
        }

        // Append to current scene
        get_parent() -> get_parent() -> add_child(grassEffect);

        // Position effect at the current grass node's global position
        grassEffect->set_global_position(get_global_position());
    }

    void Grass::_on_area_entered(Area2D* area){
        create_grass_effect();
        queue_free();
    }

}
