#include "Hurtbox.h"
#include "Effect.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/resource_loader.hpp> 

namespace godot {

    // Make sure class name matches header (you had Hitbox vs Hurtbox)
    void Hurtbox::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_area_entered", "area"), &Hurtbox::_on_area_entered);
        
        ClassDB::bind_method(D_METHOD("set_show_hit", "value"), &Hurtbox::set_show_hit);
        ClassDB::bind_method(D_METHOD("get_show_hit"), &Hurtbox::get_show_hit);

        ADD_PROPERTY(PropertyInfo(Variant::BOOL, "show_hit"), "set_show_hit", "get_show_hit");
    }
    
    //This is necessary as a fallback in case godot is not fully loaded
    Ref<PackedScene> Hurtbox::hitEffectScene = nullptr;

    void Hurtbox::_ready() {
        connect(
            "area_entered", 
            Callable(this, "_on_area_entered")
        );
    }

    void Hurtbox::_on_area_entered(Area2D* area) {
        if(show_hit){
            hitEffectScene = ResourceLoader::get_singleton()->load("res://assets/Effects/hit_effect.tscn");
            Node* hitEffectNode = hitEffectScene -> instantiate();
            Effect* hitEffect = Object::cast_to<Effect>(hitEffectNode);

            Node* main_scene = get_tree() -> get_current_scene();

            main_scene -> add_child(hitEffect);
            hitEffect -> set_global_position(get_global_position());
        }
    }

    bool Hurtbox::get_show_hit() const{
        return show_hit;
    }

    void Hurtbox::set_show_hit(bool value) {
        show_hit = value;
    }

} // namespace godot
