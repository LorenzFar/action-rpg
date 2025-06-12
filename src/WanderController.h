#ifndef WANDERCONTROLLER_H
#define WANDERCONTROLLER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace godot {

class WanderController : public Node2D {
    GDCLASS(WanderController, Node2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;
    int getWanderRange();
    void setWanderRange(int value);
    void update_target_position();
    void _on_Timer_timeout();
    int get_time_left();
    void start_wander_timer(int duration);
    Vector2 get_target_position();


private:
    Ref<RandomNumberGenerator> rng;

    Timer* timer = nullptr;
    int wanderRange = 32;
    Vector2 start_position;
    Vector2 target_position;
};

} // namespace godot

#endif // WANDERCONTROLLER_H
