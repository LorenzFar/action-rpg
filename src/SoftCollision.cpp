#include "SoftCollision.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

    void SoftCollision::_bind_methods() {
    }

    void SoftCollision::_ready() {

    }

    bool SoftCollision::is_colliding(){
        Array areas = get_overlapping_areas();
        return areas.size() > 0;
    }

    Vector2 SoftCollision::get_push_vector(){
        Array areas = get_overlapping_areas();
        Vector2 push_vector = Vector2();
        if(is_colliding()){
            Area2D *area = Object::cast_to<Area2D>(areas[0]);
            push_vector = area->get_global_position().direction_to(get_global_position());
        }
        return push_vector;
    }

} // namespace godot
