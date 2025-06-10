#ifndef HURTBOX_H
#define HURTBOX_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/packed_scene.hpp> 

namespace godot {

class Hurtbox : public Area2D {
    GDCLASS(Hurtbox, Area2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;

    void set_invincible(bool value);
    void create_hit_effect();
    void start_invincibility(double duration);

    void _on_Timer_timeout();
    void _on_Hurtbox_invincibility_started();
    void _on_Hurtbox_invincibility_ended();

private:
    Timer* timer = nullptr;
    bool invincible = false;
    static Ref<PackedScene> hitEffectScene;
};

} // namespace godot

#endif // HURTBOX_H
