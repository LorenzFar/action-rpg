#ifndef EFFECT_H
#define EFFECT_H

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

    class Effect : public AnimatedSprite2D {
        GDCLASS(Effect, AnimatedSprite2D);

    private:

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _process(double delta) override;
        void _on_animation_finished();
    };

} // namespace godot

#endif // EFFECT_H
