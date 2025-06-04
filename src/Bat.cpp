#include "Bat.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Bat::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_area_entered", "area"), &Bat::_on_area_entered);
        ClassDB::bind_method(D_METHOD("_on_Stats_no_health"), &Bat::_on_Stats_no_health);
    }

    void Bat::_ready(){
        area2D = get_node<Area2D>("Hurtbox");
        stats = get_node<Stats>("Stats");
        
        area2D -> connect(
            "area_entered",
            Callable(this, "_on_area_entered")
        );

        stats -> connect(
            "no_health",
            Callable(this, "_on_Stats_no_health")
        );

    }

    void Bat::_physics_process(double delta) {
        knockBack = knockBack.move_toward(Vector2(), 200 * delta);
        set_velocity(knockBack);
        move_and_slide();
    }

    void Bat::_on_area_entered(Hitbox* area) {
        Node2D* owner_node = Object::cast_to<Node2D>(area->get_owner());

        stats -> setHealth(stats -> getHealth() - area -> getDamage());

        Vector2 direction = (get_position() - owner_node->get_position()).normalized();
        knockBack = direction * KNOCKBACK_SPEED;
    }

    void Bat::_on_Stats_no_health(){
        queue_free();
    }
}
