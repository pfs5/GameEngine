#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GameObject.h"

class Map;

struct MapLayer
{
	friend class Map;

public:
	sf::Texture* texture = nullptr;
	float speedCoefficient = 0.f;

private:
	sf::Sprite _sprite;
};

class Map : private GameObject
{
public:
	Map(const std::string& name = "");
	~Map();

	void setMapLayer(MapLayer layer, unsigned int index);
	void move(const sf::Vector2f& distance);
	void loadColliders(const std::string& dataName);

// GameObject
public:
	virtual void update(float dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other, CollisionData _collisionData ) override;

	virtual GameObject * clone() override;

private:
	std::string _name;

	std::vector<MapLayer> _mapLayers;
};