#include "PlayerHurtSound.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

    void PlayerHurtSound::_bind_methods() {

    }

    void PlayerHurtSound::_ready() {
        connect (
            "finished",
            Callable(this, "queue_free")
        );
    }

}
