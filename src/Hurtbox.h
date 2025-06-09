#ifndef HURTBOX_H
#define HURTBOX_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp> 

namespace godot {

class Hurtbox : public Area2D {
    GDCLASS(Hurtbox, Area2D);

protected:
    static void _bind_methods();

public:
    void _ready() override;
    
    bool get_show_hit() const;
    void set_show_hit(bool value);

private:
    static Ref<PackedScene> hitEffectScene;
    bool show_hit = true;
    
    void _on_area_entered(Area2D* area);
};

} // namespace godot

#endif // HURTBOX_H
