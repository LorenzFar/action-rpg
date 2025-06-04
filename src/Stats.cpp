#include "Stats.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void Stats::_bind_methods() {
        ClassDB::bind_method(D_METHOD("setMaxHealth", "value"), &Stats::setMaxHealth);
        ClassDB::bind_method(D_METHOD("getMaxHealth"), &Stats::getMaxHealth);

        ClassDB::bind_method(D_METHOD("setHealth", "value"), &Stats::setHealth);
        ClassDB::bind_method(D_METHOD("getHealth"), &Stats::getHealth);


        ADD_PROPERTY(PropertyInfo(Variant::INT, "maxHealth"), "setMaxHealth", "getMaxHealth");
        ADD_SIGNAL(MethodInfo("no_health"));
    }

    void Stats::_ready() {
        health = maxHealth;
    }

    int Stats::getMaxHealth() const {
        return maxHealth;
    }

    void Stats::setMaxHealth(int value) {
        maxHealth = value;
    }

    void Stats::setHealth(int value){
        health = value;
        if(health <= 0){
            emit_signal("no_health");
        }
    }

    int Stats::getHealth() const {
        return health;
    }

}
