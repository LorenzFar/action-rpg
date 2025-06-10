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
        ClassDB::bind_method(D_METHOD("_on_Hurtbox_invincibility_started"), &Hurtbox::_on_Hurtbox_invincibility_started);
        ClassDB::bind_method(D_METHOD("_on_Hurtbox_invincibility_ended"), &Hurtbox::_on_Hurtbox_invincibility_ended);
        ClassDB::bind_method(D_METHOD("_on_Timer_timeout"), &Hurtbox::_on_Timer_timeout);
        
        ADD_SIGNAL(MethodInfo("invincibility_started"));
        ADD_SIGNAL(MethodInfo("invincibility_ended"));
    }
    
    //This is necessary as a fallback in case godot is not fully loaded
    Ref<PackedScene> Hurtbox::hitEffectScene = nullptr;

    void Hurtbox::_ready() {
        timer = get_node<Timer>("Timer");

        timer -> connect(
            "timeout",
            Callable(this, "_on_Timer_timeout")
        );

        connect (
            "invincibility_started",
            Callable(this, "_on_Hurtbox_invincibility_started")
        );

        connect (
            "invincibility_ended",
            Callable(this, "_on_Hurtbox_invincibility_ended")
        );
    }

    void Hurtbox::start_invincibility(double duration){
        set_invincible(true);
        timer -> start(duration);
    }

    void Hurtbox::set_invincible(bool value){
        invincible = value;

        if(invincible){
            emit_signal("invincibility_started");
        }
        else{
            emit_signal("invincibility_ended");
        }
    }

    void Hurtbox::create_hit_effect() {
        hitEffectScene = ResourceLoader::get_singleton()->load("res://assets/Effects/hit_effect.tscn");
        Node* hitEffectNode = hitEffectScene -> instantiate();
        Effect* hitEffect = Object::cast_to<Effect>(hitEffectNode);

        Node* main_scene = get_tree() -> get_current_scene();

        main_scene -> add_child(hitEffect);
        hitEffect -> set_global_position(get_global_position());
    }

    void Hurtbox::_on_Timer_timeout(){
        set_invincible(false);
    }

    void Hurtbox::_on_Hurtbox_invincibility_started(){
        set_deferred("monitoring", false);
    }

    void Hurtbox::_on_Hurtbox_invincibility_ended(){
        set_deferred("monitoring", true);
    }

} // namespace godot
