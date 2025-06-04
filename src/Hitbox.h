#ifndef HITBOX_H
#define HITBOX_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class Hitbox : public Area2D {
    GDCLASS(Hitbox, Area2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;
    int getDamage() const;
    void setDamage(int value);

private:
    int damage = 1;
};

} // namespace godot

#endif // HITBOX_H
