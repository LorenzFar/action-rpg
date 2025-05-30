#ifndef GRASSEFFECT_H
#define GRASSEFFECT_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

    class GrassEffect : public Node2D {
        GDCLASS(GrassEffect, Node2D);

    private:
        AnimatedSprite2D* animatedSprite = nullptr;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _process(double delta) override;
        void _on_animation_finished();
    };

} // namespace godot

#endif // GRASSEFFECT_H
