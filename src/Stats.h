#ifndef STATS_H
#define STATS_H

#include <godot_cpp/classes/node2d.hpp>

namespace godot {

    class Stats : public Node2D {
        GDCLASS(Stats, Node2D);

    private:
        int maxHealth = 1;
        int health;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void setMaxHealth(int value);
        int getMaxHealth() const;
        void setHealth(int value);
        int getHealth() const;
        void _init_health();

    };

} // namespace godot

#endif // STATS_H
