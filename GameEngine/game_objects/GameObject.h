#pragma once
#include <functional>
#include <vector>

#include "ITransformable.h"
#include "../physics/RigidBody.h"
#include "../physics/PhysicsLayers.h"
#include "../physics/PhysicsShared.h"

#define GAME_OBJECT_BODY() typedef GameObject Super;

class Collider;

/**
	Generic game object for the engine. All objects in the game inherit the class
	in order to work with the engine and game.
**/
class GameObject : public ITransformable{
protected:
	std::string _objectTag = "";
	std::size_t _objectTagHash;
	int _physicsLayer = 0;

	// State
	bool _isActive = true;
	
	// Physics
	RigidBody * _rigidBody;
	std::vector<Collider*> _colliders;

public:
	GameObject();
	virtual ~GameObject();

	// Game core
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;

	// Physics
	void setRigidBody(RigidBody *_rb);
	RigidBody * getRigidBody();
	void addCollider(Collider *_c);

	virtual void onCollision(Collider * _this, Collider * _other, CollisionData _collisionData);

	// Prototype pattern allows cloning of gameobjects = prefab mechanism
	virtual GameObject * clone() = 0;

protected:
	RigidBody *createRigidBody();
	Collider * createCollider(const sf::Vector2f &position = sf::Vector2f{}, const sf::Vector2f &size = sf::Vector2f{});

	#pragma region Getters and setters
public:
	inline void setObjectTag(std::string _tag) { _objectTag = _tag; _objectTagHash = std::hash<std::string>{}(_tag); };
	inline std::string getObjectTag() const { return _objectTag; };
	inline bool isObjectTag(std::string _tag) { return _objectTagHash == std::hash<std::string>{}(_tag); };

	void setObjectLayer(std::string layer);
	std::string getObjectLayer();
	bool isObjectLayer(std::string _layer) { return PhysicsLayers::layerNumber(_layer) == _physicsLayer; };

	int getLayerNumber();

	virtual void setLocalPosition(const sf::Vector2f &_pos) override;

	inline virtual void setActive(bool _a) { _isActive = _a; };
	inline bool isActive() { return _isActive; };
	#pragma endregion
};

