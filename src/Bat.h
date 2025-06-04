#ifndef BAT_H
#define BAT_H

#include "Hitbox.h"
#include "Stats.h"
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/area2d.hpp>

namespace godot {

class Bat : public CharacterBody2D {
    GDCLASS(Bat, CharacterBody2D);

    static constexpr int KNOCKBACK_SPEED = 120;

    private:
        Vector2 knockBack = Vector2();
        Area2D* area2D = nullptr; 
        Stats* stats = nullptr;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        virtual void _physics_process(double delta) override;
        void _on_area_entered(Hitbox* area);
        void _on_Stats_no_health();
    };

}

#endif 
