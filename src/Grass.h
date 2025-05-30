#ifndef GRASS_H
#define GRASS_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

    class Grass : public Node2D {
        GDCLASS(Grass, Node2D);

    private:


    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _process(double delta) override;
    };

} // namespace godot

#endif // GRASS_H
