#include "PlayerDetectionZone.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

    void PlayerDetectionZone::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_on_PlayerDetectionZone_body_entered", "body"), &PlayerDetectionZone::_on_PlayerDetectionZone_body_entered);
        ClassDB::bind_method(D_METHOD("_on_PlayerDetectionZone_body_exited", "body"), &PlayerDetectionZone::_on_PlayerDetectionZone_body_exited);
    }

    void PlayerDetectionZone::_ready() {

        connect (
            "body_entered",
            Callable(this, "_on_PlayerDetectionZone_body_entered")
        );

        connect (
            "body_exited",
            Callable(this, "_on_PlayerDetectionZone_body_exited")
        );
    }

    bool PlayerDetectionZone::can_see_player(){
        return player != nullptr;
    }

    void PlayerDetectionZone::_on_PlayerDetectionZone_body_entered(Player* body){
        //UtilityFunctions::print("Body detected");
        player = body;
    }

    void PlayerDetectionZone::_on_PlayerDetectionZone_body_exited(Player* body){
        player = nullptr;
    }

    Player* PlayerDetectionZone::getPlayer(){
        return player;
    }

} // namespace godot
