#include "Spline.h"
#include "../utility/VectorOperations.h"
#include "../settings/GameSettings.h"
#include "../debug/DebugConsole.h"
#include "../debug/Debug.h"
#include "../physics/Collider.h"
#include "../physics/RigidBody.h"

// ----------------------------------------------------------------------------
Spline::Spline()
{

}
// ----------------------------------------------------------------------------
Spline::Spline(std::initializer_list<sf::Vector2f> points):
	_points(points)
{
	initPhysics();
}
// ----------------------------------------------------------------------------
Spline::Spline(const sf::Vector2f& rootPoint, const sf::Vector2f& direction, float distance, unsigned int numberOfPoints)
{
	sf::Vector2f directionNormalized = VectorOperations::normalize(direction);

	// Construct points
	for (int i = 0; i < numberOfPoints; ++i)
	{
		sf::Vector2f point = rootPoint + directionNormalized * distance * (float) i;
		_points.push_back(point);
	}

	initPhysics();
}
// ----------------------------------------------------------------------------
Spline::Spline(std::vector<sf::Vector2f> points):
	_points(points)
{
	initPhysics();
}
// ----------------------------------------------------------------------------
void Spline::update(float dt)
{
	for (int i = 1; i < _points.size(); ++i)
	{
		std::cout << _pointColliders[i]->getPosition().x << " " << _pointColliders[i]->getPosition().y << std::endl;

		const sf::Vector2f& prevPoint = _points[i - 1];
		sf::Vector2f& curPoint = _points[i];

		sf::Vector2f directionVector = curPoint - prevPoint;
		float angle = VectorOperations::vectorAngle(directionVector, sf::Vector2f{ 0.f, 1.f });
		angle *= directionVector.x > 0.f ? -1.f : 1.f;

		float accGravity = GameSettings::GRAVITY * sin(angle);
		float accPointX = accGravity * cos(angle);
		float accPointY = accGravity * sin(angle);

		// Update position unconstrained
		//_pointVelocities[i] += sf::Vector2f{accPointX, accPointY} * dt;
		//_pointVelocities[i] -= _pointVelocities[i] * VectorOperations::norm(_pointVelocities[i]) * dt * 1e-3f;					// drag

		sf::Vector2f pointVelocity = _pointRigidBodies[i]->getVelocity();
		pointVelocity += sf::Vector2f{ accPointX, accPointY } * dt;
		pointVelocity -= pointVelocity * VectorOperations::norm(pointVelocity) * dt * 1e-3f;

		curPoint += pointVelocity * dt;
		//curPoint += _pointVelocities[i] * dt;

		// Apply distance constraint
		sf::Vector2f newDirection = curPoint - prevPoint;
		float newDistance = VectorOperations::norm(newDirection);
		newDirection /= newDistance;

		float deltaDistance = newDistance - _pointDistances[i - 1];
		curPoint -= deltaDistance * newDirection;
		pointVelocity -= deltaDistance * newDirection / dt;
		//_pointVelocities[i] -= deltaDistance * newDirection / dt;

		_pointColliders[i]->setOffset(curPoint);
		_pointRigidBodies[i]->setVelocity(pointVelocity);
	}
}
// ----------------------------------------------------------------------------
void Spline::clearPoints()
{
	_points.clear();
	_pointVelocities.clear();
	_pointDistances.clear();
	_pointRigidBodies.clear();
	_pointColliders.clear();
}
// ----------------------------------------------------------------------------
void Spline::setPointsLocal(const std::vector<sf::Vector2f>& points)
{
	_points = points;
	initPhysics();
}
// ----------------------------------------------------------------------------
const std::vector<sf::Vector2f>& Spline::getPointsLocal() const
{
	return _points;
}
// ----------------------------------------------------------------------------
void Spline::addPointLocal(const sf::Vector2f& point)
{
	_points.push_back(point);
	_pointVelocities.push_back(sf::Vector2f{ 0.f, 0.f });
	_pointRigidBodies.push_back(new RigidBody(nullptr));
	_pointColliders.push_back(createColliderForPoint(point));

	if (_points.size() > 1)
	{
		_pointDistances.push_back(VectorOperations::norm(point - _points[_points.size() - 2]));
	}
}
// ----------------------------------------------------------------------------
void Spline::movePoint(unsigned int index, const sf::Vector2f& delta)
{
	if (index < _points.size())
	{
		_points[index] += delta;
	}
}
// ----------------------------------------------------------------------------
/*override*/
void Spline::draw()
{

}
// ----------------------------------------------------------------------------
/*override*/
GameObject * Spline::clone()
{
	return new Spline(_points);
}
// ----------------------------------------------------------------------------
void Spline::initPhysics()
{
	for (int i = 0; i < _points.size(); ++i)
	{
		_pointVelocities.push_back(sf::Vector2f{ 0.f, 0.f });
		_pointRigidBodies.push_back(new RigidBody(nullptr));
		_pointColliders.push_back(createColliderForPoint(_points[i]));
	
		if (i < _points.size() - 1)
		{
			const sf::Vector2f& nextPoint = _points[i + 1];
			_pointDistances.push_back(VectorOperations::norm(nextPoint - _points[i]));
		}
	}
}
// ----------------------------------------------------------------------------
Collider* Spline::createColliderForPoint(const sf::Vector2f& position)
{
	Collider* col = createCollider(sf::Vector2f{0.f, 0.f}, sf::Vector2f{ 50.f, 50.f });
	col->setStatic(true);
	return col;
}
// ----------------------------------------------------------------------------