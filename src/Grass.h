#ifndef GRASS_H
#define GRASS_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/area2d.hpp>


namespace godot {

    class Grass : public Node2D {
        GDCLASS(Grass, Node2D);

    private:
        Area2D* area2D = nullptr; 
        void create_grass_effect();

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _on_area_entered(Area2D* area);
    };

} // namespace godot

#endif // GRASS_H
