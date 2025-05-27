#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D);

    private:
        static constexpr int MAX_SPEED = 80;
        static constexpr int ACCELERATION = 500;
        static constexpr int FRICTION = 500;

        Vector2 velocity = Vector2();

    protected:
        static void _bind_methods();

    public:
        virtual void _physics_process(double delta) override;
    };

}

#endif 
