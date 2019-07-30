#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Color.hpp"
class DebugConsoleLogEntry
{
public:
	DebugConsoleLogEntry(const sf::Vector2f& position = sf::Vector2f{ 0.f, 0.f }, const sf::Vector2f& size = sf::Vector2f{100.f, 100.f});

	void setText(const std::string& str);

	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f& getPosition() const;

	void setSize(const sf::Vector2f& size);
	const sf::Vector2f& getSize() const;

	void setColor(const sf::Color& color);

	void draw() const;

private:
	sf::RectangleShape _backgroundShape;
	sf::Text _textShape;

	sf::Vector2f _position;
	sf::Vector2f _size;
};