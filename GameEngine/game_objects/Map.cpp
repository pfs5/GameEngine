#include "Map.h"
#include "../rendering/Rendering.h"
#include "../utility/json.h"
#include "../config_manager/ConfigManager.h"

#include <fstream>
#include "../physics/Collider.h"
#include "../physics/PhysicsEngine.h"

Map::Map(const std::string& name):
	_name{name}
{
	auto rb = createRigidBody();
	rb->setGravity(false);

	setObjectTag("terrain");
}

Map::~Map()
{

}

void Map::setMapLayer(MapLayer layer, unsigned int index)
{
	while(_mapLayers.size() < index + 1)
	{
		_mapLayers.push_back(MapLayer{});
	}

	layer._sprite.setTexture(*layer.texture);
	_mapLayers[index] = layer;
}

void Map::move(const sf::Vector2f& distance)
{
	for (auto& layer : _mapLayers)
	{
		layer._sprite.move(distance * layer.speedCoefficient);
	}
}

void Map::loadColliders(const std::string& dataName)
{
	std::string path = ConfigManager::getInstance().getString("data-paths", "map-data-folder") + dataName + ".json";

	std::ifstream file{ path };
	if (file.is_open()) 
	{
		nlohmann::json data;
		file >> data;

		for (const auto& col : data["colliders"])
		{
			float x = col["x"];
			float y = col["y"];
			float width = col["width"];
			float height = col["height"];

			auto newCollider = createCollider(sf::Vector2f{ x + width / 2.f, y + height / 2 }, sf::Vector2f{ width, height });
			newCollider->setTrigger(false, getRigidBody());
			newCollider->setStatic(true);
		}
	}
}

void Map::update(float dt)
{

}

void Map::draw()
{
	for (auto& layer : _mapLayers)
	{
		Rendering::draw(layer._sprite);
	}
}

void Map::onCollision(Collider * _this, Collider * _other, CollisionData _collisionData)
{
}

GameObject * Map::clone()
{
	throw std::logic_error("The method or operation is not implemented.");
}

