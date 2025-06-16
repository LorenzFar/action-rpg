#include "PlayerCamera.h"
#include <godot_cpp/classes/node.hpp>


namespace godot {

    void PlayerCamera::_bind_methods() {
    }

    void PlayerCamera::_ready() {
        topLeft = get_node<Marker2D>("Limits/TopLeft");
        bottomRight = get_node<Marker2D>("Limits/BottomRight");

        set_limit(SIDE_TOP, topLeft->get_position().y);
        set_limit(SIDE_LEFT, topLeft->get_position().x);
        set_limit(SIDE_BOTTOM, bottomRight->get_position().y);
        set_limit(SIDE_RIGHT, bottomRight->get_position().x);
    }

} // namespace godot
