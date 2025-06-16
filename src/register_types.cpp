#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "Player.h"
#include "Grass.h"
#include "Effect.h"
#include "Bat.h"
#include "Stats.h"
#include "Hitbox.h"
#include "Hurtbox.h"
#include "PlayerDetectionZone.h"
#include "HeartUI.h"
#include "SoftCollision.h"
#include "PlayerHurtSound.h"
#include "PlayerCamera.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Stats);
	GDREGISTER_CLASS(Player);
	GDREGISTER_CLASS(Grass);
	GDREGISTER_CLASS(Effect);
	GDREGISTER_CLASS(Bat);
	GDREGISTER_CLASS(Hitbox);
	GDREGISTER_CLASS(Hurtbox);
	GDREGISTER_CLASS(HeartUI);
	GDREGISTER_CLASS(PlayerDetectionZone);
	GDREGISTER_CLASS(SoftCollision);
	GDREGISTER_CLASS(WanderController);
	GDREGISTER_CLASS(PlayerHurtSound);
	GDREGISTER_CLASS(PlayerCamera);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}