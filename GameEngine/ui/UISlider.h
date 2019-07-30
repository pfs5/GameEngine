#pragma once
#include "UIElement.h"
#include <SFML/Graphics/RectangleShape.hpp>

class UISlider : public UIElement
{
public:
	UISlider(const sf::Vector2f &size = sf::Vector2f{ 0.f, 0.f }, 
		const sf::Color& backgroundColor = sf::Color::White,
		const sf::Color& fillColor = sf::Color::Cyan,
		const sf::Color& outlineColor = sf::Color::Black,
		float outlineThickness = 2.f);
	~UISlider() override;

	void setLocalPosition(const sf::Vector2f& _pos) override;
	void draw() override;
	void setVisible(bool value) override;

	// Slider methods
	void setValue(float value);
	float getValue() const;

	void setSize(const sf::Vector2f& size);

private:
	// UI
	bool _isVisible;

	// Data
	sf::Vector2f _size;
	float _value;			// [0, 1] range

	// Visuals
	sf::Color _bgColor;
	sf::Color _fgColor;
	sf::Color _outlineColor;
	float _outlineThickness;
	
	sf::RectangleShape _backgroundShape;
	sf::RectangleShape _fillShape;

private:
	void initVisuals(const sf::Color &bgColor, const sf::Color &fillColor, const sf::Color& outlineColor, float outlineThickness);
	void updateShape();
};
