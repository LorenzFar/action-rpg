#include "WanderController.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

    void WanderController::_bind_methods() {
        ClassDB::bind_method(D_METHOD("setWanderRange", "value"), &WanderController::setWanderRange);
        ClassDB::bind_method(D_METHOD("getWanderRange"), &WanderController::getWanderRange);

        ClassDB::bind_method(D_METHOD("_on_Timer_timeout"), &WanderController::_on_Timer_timeout);

        ADD_PROPERTY(PropertyInfo(Variant::INT, "WanderRange"), "setWanderRange", "getWanderRange");
    }

    void WanderController::_ready() {
        rng.instantiate();
        rng->randomize();

        timer = get_node<Timer>("Timer");

        start_position = get_global_position();
        target_position = get_global_position();

        update_target_position();
    }

    int WanderController::getWanderRange(){
        return wanderRange;
    }

    void WanderController::setWanderRange(int value){
        wanderRange = value;
    }

    void WanderController::update_target_position(){
        Vector2 target_vector = Vector2(rng -> randf_range(-wanderRange, wanderRange), rng -> randf_range(-wanderRange, wanderRange));
        target_position = start_position + target_vector;
    }

    int WanderController::get_time_left(){
        return timer -> get_time_left();
    }

    void WanderController::_on_Timer_timeout(){
        update_target_position();
    }

    void WanderController::start_wander_timer(int duration){
        timer->set_wait_time(duration);
        timer->start();
    }

    Vector2 WanderController::get_target_position(){
        return target_position;
    }

} // namespace godot
