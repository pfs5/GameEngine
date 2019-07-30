#include "HUDButton.h"
#include "../rendering/Rendering.h"
#include "../debug/DebugConsole.h"
#include "../resource_management/ResourceManager.h"

// ----------------------------------------------------------------------------
HUDButton::HUDButton(const sf::Vector2f& size, const sf::Vector2f& position):
	_size{size},
	_position{position},
	_buttonText{ "", *ResourceManager::getInstance().getFont("couriernew1") }
{
	_backgroundShape.setOrigin(0.f, 0.f);
	_backgroundShape.setSize(size);
	_backgroundShape.setFillColor(sf::Color{0, 0, 0, 150});

	_buttonText.setFillColor(sf::Color{255, 255, 255});
	_buttonText.setCharacterSize(15u);
	_buttonText.setStyle(sf::Text::Style::Bold);

	setPosition(position);
}
// ----------------------------------------------------------------------------
void HUDButton::draw() const
{
	Rendering::draw(_backgroundShape);
	Rendering::draw(_buttonText);
}
// ----------------------------------------------------------------------------
void HUDButton::setSize(const sf::Vector2f& size)
{
	_size = size;
	_backgroundShape.setSize(size);
}
// ----------------------------------------------------------------------------
void HUDButton::setPosition(const sf::Vector2f& pos)
{
	_position = pos;
	_backgroundShape.setPosition(pos);
	_buttonText.setPosition(pos + sf::Vector2f{ 15.f, 0.f });
}
// ----------------------------------------------------------------------------
void HUDButton::setText(const std::string& text)
{
	_buttonText.setString(sf::String{ text });
}
// ----------------------------------------------------------------------------
bool HUDButton::getBounds(sf::Vector2f* outMin, sf::Vector2f* outMax)
{
	if (outMin == nullptr || outMax == nullptr)
	{
		return false;
	}

	*outMin = _position;
	*outMax = _position + _size;

	return true;
}
// ----------------------------------------------------------------------------
void HUDButton::setCallback_OnClicked(void(*fun) (void))
{
	_onClickedDelegate = fun;
}
// ----------------------------------------------------------------------------
void HUDButton::onClicked()
{
	if (_onClickedDelegate != nullptr)
	{
		_onClickedDelegate();
	}
}
// ----------------------------------------------------------------------------