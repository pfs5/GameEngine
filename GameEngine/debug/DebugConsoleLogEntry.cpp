#include "DebugConsoleLogEntry.h"
#include "../rendering/Rendering.h"
#include "../resource_management/ResourceManager.h"
// ----------------------------------------------------------------------------
DebugConsoleLogEntry::DebugConsoleLogEntry(const sf::Vector2f& position, const sf::Vector2f& size):
	_textShape{"", *ResourceManager::getInstance().getFont("couriernew1")},
	_position{position},
	_size{size}
{
	_backgroundShape.setFillColor(sf::Color::Transparent);

	_textShape.setFillColor(sf::Color::Black);
	_textShape.setCharacterSize(15u);
	_textShape.setStyle(sf::Text::Style::Bold);

	setSize(_size);
	setPosition(_position);
}
// ----------------------------------------------------------------------------
void DebugConsoleLogEntry::setText(const std::string& str)
{
	_textShape.setString(sf::String(str));
}
// ----------------------------------------------------------------------------
void DebugConsoleLogEntry::setPosition(const sf::Vector2f& position)
{
	_position = position;
	_backgroundShape.setPosition(position);
	_textShape.setPosition(position);
}
// ----------------------------------------------------------------------------
const sf::Vector2f& DebugConsoleLogEntry::getPosition() const
{
	return _position;
}
// ----------------------------------------------------------------------------
void DebugConsoleLogEntry::setSize(const sf::Vector2f& size)
{
	_size = size;
	_backgroundShape.setSize(size);
}
// ----------------------------------------------------------------------------
const sf::Vector2f& DebugConsoleLogEntry::getSize() const
{
	return _size;
}
// ----------------------------------------------------------------------------
void DebugConsoleLogEntry::setColor(const sf::Color& color)
{
	_textShape.setFillColor(color);
}
// ----------------------------------------------------------------------------
void DebugConsoleLogEntry::draw() const
{
	Rendering::draw(_backgroundShape);
	Rendering::draw(_textShape);
}
// ----------------------------------------------------------------------------