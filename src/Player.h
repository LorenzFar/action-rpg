#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

using AnimationState = godot::AnimationNodeStateMachinePlayback;

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

    private:
        static constexpr int MAX_SPEED = 80;
        static constexpr int ACCELERATION = 500;
        static constexpr int FRICTION = 500;

        enum {
            MOVE,
            ROLL,
            ATTACK
        };

        Vector2 velocity = Vector2();
        AnimationPlayer* animationPlayer = nullptr;
        AnimationTree* animationTree = nullptr;
        AnimationState* animationState = nullptr;
        int state = MOVE;

        void move_state(double delta);
        void attack_state(double delta);

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        virtual void _physics_process(double delta) override;
    };

}

#endif 
