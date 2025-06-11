#include "Stats.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Stats::_bind_methods() {
        ClassDB::bind_method(D_METHOD("setMaxHealth", "value"), &Stats::setMaxHealth);
        ClassDB::bind_method(D_METHOD("getMaxHealth"), &Stats::getMaxHealth);

        ClassDB::bind_method(D_METHOD("setHealth", "value"), &Stats::setHealth);
        ClassDB::bind_method(D_METHOD("getHealth"), &Stats::getHealth);

        ClassDB::bind_method(D_METHOD("_init_health"), &Stats::_init_health);


        ADD_PROPERTY(PropertyInfo(Variant::INT, "maxHealth"), "setMaxHealth", "getMaxHealth");

        ADD_SIGNAL(MethodInfo("no_health"));
        ADD_SIGNAL(MethodInfo("max_health_changed", PropertyInfo(Variant::INT, "value")));
        ADD_SIGNAL(MethodInfo("health_changed", PropertyInfo(Variant::INT, "value")));
    }

    void Stats::_ready() {
        //Necessary to ensure that signal is attached properly to HeartUI
        call_deferred("_init_health");
    }

    int Stats::getMaxHealth() const {
        return maxHealth;
    }

    void Stats::setMaxHealth(int value) {
        maxHealth = value;
        setHealth(MIN(health, maxHealth));
        emit_signal("max_health_changed", maxHealth);
    }

    void Stats::setHealth(int value){
        health = value;
        emit_signal("health_changed", health);
        if(health <= 0){
            emit_signal("no_health");
        }
    }

    int Stats::getHealth() const {
        return health;
    }

    void Stats::_init_health(){
        health = maxHealth;
        setMaxHealth(maxHealth);
        setHealth(maxHealth);
    }
}
