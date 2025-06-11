#ifndef SOFTCOLLISION_H
#define SOFTCOLLISION_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class SoftCollision : public Area2D {
    GDCLASS(SoftCollision, Area2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;
    bool is_colliding();
    Vector2 get_push_vector();

private:

};

} // namespace godot

#endif // SOFT_COLLISIONH
