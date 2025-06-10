#ifndef PLAYER_H
#define PLAYER_H

#include "Hitbox.h"
#include "Hurtbox.h"
#include "Stats.h"
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

using AnimationState = godot::AnimationNodeStateMachinePlayback;

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

    private:
        static constexpr int MAX_SPEED = 80;
        static constexpr int ACCELERATION = 500;
        static constexpr int FRICTION = 500;
        static constexpr int ROLL_SPEED = 125;

        enum {
            MOVE,
            ROLL,
            ATTACK
        };

        Vector2 velocity = Vector2();
        Vector2 roll_vector = Vector2(0, 1);
        
        Stats* stats = nullptr;
        Hurtbox* hurtbox = nullptr;
        AnimationPlayer* animationPlayer = nullptr;
        AnimationTree* animationTree = nullptr;
        AnimationState* animationState = nullptr;

        int state = MOVE;

        void move_state(double delta);

        void attack_state(double delta);
        void attack_animation_finished();

        void roll_animation_finished();
        void roll_state(double delta);

        void move();

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        virtual void _process(double delta) override;
        void _on_area_entered(Hitbox* area);
    };

}

#endif 
