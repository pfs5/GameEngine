#pragma once
#include "UIElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class UILine : public UIElement
{
public:
	UILine(float thickness = 1.f, sf::Color color = sf::Color::Red);
	~UILine();

	// UIElement
	void draw() override;
	void setVisible(bool value) override;

	// UILine
	void setStartPoint(const sf::Vector2f &p);
	void setEndPoint(const sf::Vector2f &p);
	void setThickness(float value);
	void setColor(const sf::Color& color);

private:
	bool _isVisible;

	sf::RectangleShape _shape;
	float _thickness;

	sf::Vector2f _startPoint;
	sf::Vector2f _endPoint;

private:
	void updateShape();
};

