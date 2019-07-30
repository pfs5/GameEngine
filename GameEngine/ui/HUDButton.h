#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "HUD.h"

// ----------------------------------------------------------------------------
class HUDButton
{
	friend class HUD;

public:
	HUDButton(const sf::Vector2f& size, const sf::Vector2f& position);

	void draw() const;
	
	void setSize(const sf::Vector2f& size);
	void setPosition(const sf::Vector2f& pos);
	void setText(const std::string& text);

	bool getBounds(sf::Vector2f* outMin, sf::Vector2f* outMax);

	void setCallback_OnClicked(void(*fun) (void));

private:
	sf::Vector2f _size;
	sf::Vector2f _position;

	// --- Visuals ---
	sf::RectangleShape _backgroundShape;
	sf::Text _buttonText;

	// --- Delegates ---
	void (*_onClickedDelegate)(void);

private:
	virtual void onClicked();
};
// ----------------------------------------------------------------------------