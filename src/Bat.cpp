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

        ClassDB::bind_method(D_METHOD("_on_Hurtbox_invincibility_started"), &Bat::_on_Hurtbox_invincibility_started);
        ClassDB::bind_method(D_METHOD("_on_Hurtbox_invincibility_ended"), &Bat::_on_Hurtbox_invincibility_ended);
    }

    void Bat::_ready(){
        rng.instantiate();
        rng->randomize();

        animationPlayer = get_node<AnimationPlayer>("AnimationPlayer");
        hurtbox = get_node<Hurtbox>("Hurtbox");
        stats = get_node<Stats>("Stats");
        playerDetectionZone = get_node<PlayerDetectionZone>("PlayerDetectionZone");
        animatedSprite2D = get_node<AnimatedSprite2D>("AnimatedSprite2D");
        softCollision = get_node<SoftCollision>("SoftCollision");
        wanderController = get_node<WanderController>("WanderController");
        
        hurtbox -> connect(
            "area_entered",
            Callable(this, "_on_area_entered")
        );

        hurtbox -> connect (
            "invincibility_started",
            Callable(this, "_on_Hurtbox_invincibility_started")
        );

        hurtbox -> connect (
            "invincibility_ended",
            Callable(this, "_on_Hurtbox_invincibility_ended")
        );

        stats -> connect(
            "no_health",
            Callable(this, "_on_Stats_no_health")
        );
        
        //Append to random list for randomly picking state
        random_list.append(IDLE);
        random_list.append(WANDER);

        state = pick_random_state();
    }

    void Bat::_physics_process(double delta) {
        knockBack = knockBack.move_toward(Vector2(), FRICTION * delta);
        set_velocity(knockBack);
        move_and_slide();

        switch (state)
        {
            case IDLE: {
                velocity = velocity.move_toward(Vector2(), FRICTION * delta);
                seek_player();

                if (wanderController->get_time_left() == 0) {
                    wanderController -> update_target_position();
                    update_wander();
                }
                break;
            }

            case WANDER: {
                seek_player();

                if (wanderController->get_time_left() == 0) {
                    wanderController -> update_target_position();
                    update_wander();
                }

                accelerate_towards_point(wanderController -> get_target_position(), delta);

                if(get_global_position().distance_to(wanderController -> get_target_position()) <= WANDER_TARGET_RANGE ){
                    update_wander();
                }
                break;
            }

            case CHASE: {
                if (playerDetectionZone->can_see_player()) {
                    Player* player = playerDetectionZone->getPlayer();
                    accelerate_towards_point(player -> get_global_position(), delta);
                } else {
                    state = IDLE;
                }

                // Flip Animation if player is on the right side 
                animatedSprite2D->set_flip_h(velocity.x < 0);
                break;
            }

            default:
                break;
        }

        if (softCollision->is_colliding()) {
            velocity += softCollision->get_push_vector() * delta * 400;
        }

        set_velocity(velocity);
        move_and_slide();
    }

    void Bat::accelerate_towards_point(Vector2 point, double delta){
        Vector2 direction = get_global_position().direction_to(point);
        velocity = velocity.move_toward(direction * MAX_SPEED, ACCELERATION * delta);
        animatedSprite2D->set_flip_h(velocity.x < 0);
    }

    void Bat::update_wander(){
        state = pick_random_state();
        wanderController->start_wander_timer(rng -> randf_range(1, 3));
    }

    void Bat::seek_player(){
        if(playerDetectionZone -> can_see_player()){
            state = CHASE;
        }
    }

    int Bat::pick_random_state(){
        return random_list.pick_random();
    }

    void Bat::_on_area_entered(Hitbox* area) {
        Node2D* owner_node = Object::cast_to<Node2D>(area->get_owner());

        stats -> setHealth(stats -> getHealth() - area -> getDamage());

        Vector2 direction = (get_position() - owner_node->get_position()).normalized();
        knockBack = direction * KNOCKBACK_SPEED;

        hurtbox -> create_hit_effect();

        hurtbox -> start_invincibility(0.4);
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

    void Bat::_on_Hurtbox_invincibility_started(){
        animationPlayer -> play("Start");
    }

    void Bat::_on_Hurtbox_invincibility_ended(){
        animationPlayer -> play("Stop");
    }

}
