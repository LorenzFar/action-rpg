#include "HeartUI.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

void HeartUI::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_hearts", "value"), &HeartUI::set_hearts);
    ClassDB::bind_method(D_METHOD("set_max_hearts", "value"), &HeartUI::set_max_hearts);
}

void HeartUI::_ready() {
    heartUIEmpty = get_node<TextureRect>("HeartUIEmpty");
    heartUIFull = get_node<TextureRect>("HeartUIFull");
    stats = get_node<Stats>(NodePath("/root/PlayerStats"));

    if (stats) {
        stats->connect(
            "health_changed", 
            Callable(this, "set_hearts")
        );

        stats->connect(
            "max_health_changed", 
            Callable(this, "set_max_hearts")
        );
    
    }   
}

void HeartUI::set_hearts(int value) {
    hearts = CLAMP(value, 1, max_hearts);
    if (heartUIFull) {
        Vector2 size = heartUIFull->get_size();
        size.x = hearts * 15;
        heartUIFull->set_size(size);
    }
}

void HeartUI::set_max_hearts(int value) {
    max_hearts = MAX(value, 1);
    set_hearts(MIN(hearts, max_hearts));

    if (heartUIEmpty) {
        Vector2 size = heartUIEmpty->get_size();
        size.x = max_hearts * 15;
        heartUIEmpty->set_size(size);
    }
}



}
