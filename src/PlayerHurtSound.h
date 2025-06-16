#ifndef PLAYERHURTSOUND_H
#define PLAYERHURTSOUND_H

#include <godot_cpp/classes/audio_stream_player.hpp>

namespace godot {

    class PlayerHurtSound : public AudioStreamPlayer {
        GDCLASS(PlayerHurtSound, AudioStreamPlayer);

    private:

    protected:
        static void _bind_methods();

    public:
        void _ready() override;

    };

} // namespace godot

#endif // PLAYERHURTSOUND_H
