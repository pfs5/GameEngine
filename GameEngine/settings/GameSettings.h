#pragma once

/**
	Holds global game settings and parameters.
**/
namespace GameSettings {
	const std::string VERSION = "0.1a";

	// Debug outputs
	const bool PRINT_FPS = true;
	//const bool SHOW_COLLIDERS = true;
	const bool SHOW_DEBUG_VISUALS = false;

	// Physics
	const float GLOBAL_SCALE = 1e2;	// how many meters is one unit in the game (screen)
	const float GRAVITY = 9.81f * GLOBAL_SCALE;
}