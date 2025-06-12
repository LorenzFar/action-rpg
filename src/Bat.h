#ifndef BAT_H
#define BAT_H

#include "Hitbox.h"
#include "WanderController.h"
#include "Hurtbox.h"
#include "SoftCollision.h"
#include "Stats.h"
#include "PlayerDetectionZone.h"
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/area2d.hpp>

namespace godot {

class Bat : public CharacterBody2D {
    GDCLASS(Bat, CharacterBody2D);

    static constexpr int KNOCKBACK_SPEED = 120;
    static constexpr int MAX_SPEED = 50;
    static constexpr int ACCELERATION = 300;
    static constexpr int FRICTION = 200; 
    static constexpr int WANDER_TARGET_RANGE = 4;

    enum {
        IDLE,
        WANDER,
        CHASE
    };

    private:
        Ref<RandomNumberGenerator> rng;

        Vector2 velocity = Vector2();
        Vector2 knockBack = Vector2();
        Hurtbox* hurtbox = nullptr;
        SoftCollision* softCollision = nullptr;
        AnimatedSprite2D* animatedSprite2D = nullptr;
        PlayerDetectionZone* playerDetectionZone = nullptr;
        Stats* stats = nullptr;
        WanderController* wanderController = nullptr;
        int state = CHASE;
        Array random_list;

        void create_death_effect();

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        virtual void _physics_process(double delta) override;
        void _on_area_entered(Hitbox* area);
        void _on_Stats_no_health();
        void seek_player();
        void accelerate_towards_point(Vector2 point, double delta);
        int pick_random_state();
        void update_wander();
    };

}

#endif 
