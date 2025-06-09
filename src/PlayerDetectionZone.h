#ifndef PlAYERDETECTIONZONE_H
#define PlAYERDETECTIONZONE_H

#include "Player.h"
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class PlayerDetectionZone : public Area2D {
    GDCLASS(PlayerDetectionZone, Area2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _on_PlayerDetectionZone_body_entered(Player* body);
    void _on_PlayerDetectionZone_body_exited(Player* body);
    bool can_see_player();
    Player* getPlayer();

private:
    Player* player = nullptr;
};

} // namespace godot

#endif // PLAYERDETECTIONZONE_H
