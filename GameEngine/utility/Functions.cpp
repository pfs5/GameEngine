#include "Functions.h"

Functions::LinearFunction::LinearFunction(float k, float l) :
	_k {k},
	_l {l}
{
}

Functions::Function * Functions::LinearFunction::copy() const
{
	return new LinearFunction(_k, _l);
}

float Functions::LinearFunction::value(float in)
{
	return _k * in + _l;
}

Functions::LinearFunction Functions::LinearFunction::twoPoints(sf::Vector2f p1, sf::Vector2f p2)
{
	float k = (p2.y - p1.y) / (p2.x - p1.x);
	float l = -(p2.y - p1.y) / (p2.x - p1.x) * p1.x + p1.y;

	return LinearFunction{ k, l };
}
