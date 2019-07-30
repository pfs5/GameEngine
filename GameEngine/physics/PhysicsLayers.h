#pragma once
#include <vector>
#include <string>

/**
	Enables the engine to ignore collisions between certain objects in the game.
**/
namespace PhysicsLayers {
	const int NUMBER_OF_LAYERS = 4;

	const std::vector<std::vector<bool>> fillIgnoreMatrix();

	const std::vector<std::string> layers {"Default", "Player", "Map", "PlayerProjectile"};
	const std::vector<std::vector<bool>> layerIgnoreMatrix = fillIgnoreMatrix();

	int layerNumber(std::string _name);

	std::string layerName(int _number);
}