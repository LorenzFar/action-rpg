#include "Bat.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource_loader.hpp> 
#include <godot_cpp/classes/packed_scene.hpp> 
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {

    void Bat::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_area_entered", "area"), &Bat::_on_area_entered);
        ClassDB::bind_method(D_METHOD("_on_Stats_no_health"), &Bat::_on_Stats_no_health);
    }

    void Bat::_ready(){
        hurtbox = get_node<Hurtbox>("Hurtbox");
        stats = get_node<Stats>("Stats");
        playerDetectionZone = get_node<PlayerDetectionZone>("PlayerDetectionZone");
        animatedSprite2D = get_node<AnimatedSprite2D>("AnimatedSprite2D");
        
        hurtbox -> connect(
            "area_entered",
            Callable(this, "_on_area_entered")
        );

        stats -> connect(
            "no_health",
            Callable(this, "_on_Stats_no_health")
        );

    }

    void Bat::_physics_process(double delta) {
        knockBack = knockBack.move_toward(Vector2(), FRICTION * delta);
        set_velocity(knockBack);
        move_and_slide();

        switch (state)
        {
        case IDLE:
            velocity = velocity.move_toward(Vector2(), FRICTION * delta);
            seek_player();
            break;
        case WANDER:
            break;
        case CHASE:
            if(playerDetectionZone -> can_see_player()){
                Player* player = playerDetectionZone -> getPlayer();
                Vector2 direction = (player -> get_global_position() - get_global_position()).normalized();
                velocity = velocity.move_toward(direction * MAX_SPEED, ACCELERATION * delta);
            }
            else{
                state = IDLE;
            }
            //Flip Animation if player on the right side 
            animatedSprite2D->set_flip_h(velocity.x < 0);
        default:
            break;
        }

        set_velocity(velocity);
        move_and_slide();
    }

    void Bat::seek_player(){
        if(playerDetectionZone -> can_see_player()){
            state = CHASE;
        }
    }

    void Bat::_on_area_entered(Hitbox* area) {
        Node2D* owner_node = Object::cast_to<Node2D>(area->get_owner());

        stats -> setHealth(stats -> getHealth() - area -> getDamage());

        Vector2 direction = (get_position() - owner_node->get_position()).normalized();
        knockBack = direction * KNOCKBACK_SPEED;

        hurtbox -> create_hit_effect();
    }

    void Bat::create_death_effect(){
        Ref<PackedScene> deathEffectScene = ResourceLoader::get_singleton()->load("res://assets/Effects/enemy_death_effect.tscn");
        if (deathEffectScene.is_null()) {
            UtilityFunctions::print("Failed to load deathEffect scene.");
            return;
        }

        Node *deathEffectNode = deathEffectScene->instantiate();
        AnimatedSprite2D *deathEffect = Object::cast_to<AnimatedSprite2D>(deathEffectNode);
        if (!deathEffect) {
            UtilityFunctions::print("deathEffect is not a AnimatedSprite2D.");
            return;
        }

        // Append to current scene
        get_parent() -> add_child(deathEffect);

        // Position effect at the current bat node's global position
        deathEffect->set_global_position(get_global_position());
    }

    void Bat::_on_Stats_no_health(){
        queue_free();
        create_death_effect();
    }

}
