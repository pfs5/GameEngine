#pragma once
#include "SFML/System/Vector2.hpp"
struct CollisionData
{
public:
	sf::Vector2f CollisionAxis	= sf::Vector2f{ 0.f, 0.f };
	sf::Vector2f PositionDelta	= sf::Vector2f{ 0.f, 0.f };
	sf::Vector2f NewVelocity	= sf::Vector2f{ 0.f, 0.f };
};