#pragma once
#include <initializer_list>
#include "GameObject.h"

// ----------------------------------------------------------------------------
class RigidBody;
class Collider;
// ----------------------------------------------------------------------------
class Spline : public GameObject {

public:
	Spline();
	Spline(std::initializer_list<sf::Vector2f> points);
	Spline(std::vector<sf::Vector2f> points);
	Spline(const sf::Vector2f& rootPoint, const sf::Vector2f& direction, float distance, unsigned int numberOfPoints);

	// To be called for physics to work.
	void update(float dt);

	void clearPoints();
	void setPointsLocal(const std::vector<sf::Vector2f>& points);
	const std::vector<sf::Vector2f>& getPointsLocal() const;
	void addPointLocal(const sf::Vector2f& point);
	void movePoint(unsigned int index, const sf::Vector2f& delta);


// GameObject
public:
	virtual void draw() override;
	virtual GameObject * clone() override;

private:
	std::vector<sf::Vector2f>	_points;
	std::vector<sf::Vector2f>	_pointVelocities;
	std::vector<RigidBody*>		_pointRigidBodies;
	std::vector<Collider*>		_pointColliders;
	std::vector<float>			_pointDistances;

private:
	void initPhysics();
	Collider* createColliderForPoint(const sf::Vector2f& position);
};
// ----------------------------------------------------------------------------