#include "UILine.h"
#include "../utility/VectorOperations.h"
#include "../rendering/Rendering.h"

UILine::UILine(float thickness, sf::Color color) :
	_isVisible{ true },
	_thickness{ thickness }
{
	_shape.setOrigin(0.f, thickness / 2.f);
	_shape.setFillColor(color);
}

UILine::~UILine()
{
}

void UILine::draw()
{
	if (!_isVisible)
	{
		return;
	}

	Rendering::draw(_shape);
}

void UILine::setVisible(bool value)
{
	_isVisible = value;
}

void UILine::setStartPoint(const sf::Vector2f & p)
{
	_startPoint = p;
	updateShape();
}

void UILine::setEndPoint(const sf::Vector2f & p)
{
	_endPoint = p;
	updateShape();
}

void UILine::setThickness(float value)
{
	_thickness = value;

	updateShape();
}

void UILine::setColor(const sf::Color& color)
{
	_shape.setFillColor(color);
}

void UILine::updateShape()
{
	_shape.setSize(sf::Vector2f{ VectorOperations::norm(_endPoint - _startPoint), _thickness });
	_shape.setOrigin(0.f, _thickness / 2.f);
	_shape.setPosition(_startPoint);

	float angle = Util::radianToDegree(VectorOperations::vectorAngle((_endPoint - _startPoint), sf::Vector2f{ 1.f, 0.f }));
	angle *= _endPoint.y < _startPoint.y ? -1.f : 1.f;
	_shape.setRotation(angle);
}
