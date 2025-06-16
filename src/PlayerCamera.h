#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class PlayerCamera : public Camera2D {
    GDCLASS(PlayerCamera, Camera2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;

private:
    Marker2D* topLeft = nullptr;
    Marker2D* bottomRight = nullptr;

};

} // namespace godot

#endif // PLAYERCAMERA_H
