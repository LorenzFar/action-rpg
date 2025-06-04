#include "Hitbox.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

    void Hitbox::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_damage", "value"), &Hitbox::setDamage);
        ClassDB::bind_method(D_METHOD("get_damage"), &Hitbox::getDamage);

        ADD_PROPERTY(PropertyInfo(Variant::INT, "damage"), "set_damage", "get_damage");
    }

    void Hitbox::_ready() {

    }

    int Hitbox::getDamage() const{
        return damage;
    }

    void Hitbox::setDamage(int value) {
        damage = value;
    }

} // namespace godot
