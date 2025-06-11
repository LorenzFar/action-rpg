#ifndef HEARTUI_H
#define HEARTUI_H

#include "Stats.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

namespace godot {

    class HeartUI : public Control {
        GDCLASS(HeartUI, Control);

    private:
        int max_hearts;
        int hearts;
        TextureRect* heartUIFull = nullptr;
        TextureRect* heartUIEmpty = nullptr;
        Stats* stats = nullptr;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_hearts(int value);
        void set_max_hearts(int value);
        //void _connect_to_stats();
    };

} // namespace godot

#endif // HEARTUI_H
