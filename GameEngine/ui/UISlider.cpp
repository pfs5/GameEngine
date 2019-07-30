#include "UISlider.h"
#include "../rendering/Rendering.h"
#include "../utility/Util.h"

UISlider::UISlider(const sf::Vector2f &size, const sf::Color &backgroundColor, const sf::Color &fillColor, const sf::Color& outlineColor, float outlineThickness) :
	_isVisible{ true },
	_size{ size },
	_value{ 0.f },
	_bgColor{ backgroundColor },
	_fgColor{ fillColor },
	_outlineColor{ outlineColor },
	_outlineThickness{ outlineThickness }
{
	initVisuals(backgroundColor, fillColor, outlineColor, outlineThickness);
}

UISlider::~UISlider()
{
}

void UISlider::setLocalPosition(const sf::Vector2f & _pos)
{
	UIElement::setLocalPosition(_pos);
}

void UISlider::draw()
{
	if (!_isVisible)
	{
		return;
	}

	_backgroundShape.setPosition(_globalPosition);
	_fillShape.setPosition(_globalPosition - _size / 2.f);

	Rendering::draw(_backgroundShape);
	Rendering::draw(_fillShape);
}

void UISlider::setVisible(bool value)
{
	_isVisible = value;
}

void UISlider::setValue(float value)
{
	_value = Util::clamp(value, 0.f, 1.f);
	updateShape();
}

float UISlider::getValue() const
{
	return _value;
}

void UISlider::setSize(const sf::Vector2f& size)
{
	_size = size;
	initVisuals(_bgColor, _fgColor, _outlineColor, _outlineThickness);
}

void UISlider::initVisuals(const sf::Color &bgColor, const sf::Color &fillColor, const sf::Color& outlineColor, float outlineThickness)
{
	_backgroundShape.setSize(_size);
	_backgroundShape.setOrigin(_size / 2.f);
	_backgroundShape.setFillColor(bgColor);
	_backgroundShape.setOutlineColor(outlineColor);
	_backgroundShape.setOutlineThickness(outlineThickness);

	_fillShape.setSize(sf::Vector2f{ _size.x * _value, _size.y });
	_fillShape.setOrigin(sf::Vector2f{ 0.f, 0.f });
	_fillShape.setFillColor(fillColor);
	//_fillShape.setOutlineColor(outlineColor);
	//_fillShape.setOutlineThickness(outlineThickness);
}

void UISlider::updateShape()
{
	_fillShape.setSize(sf::Vector2f{ _size.x * _value, _size.y });
}
