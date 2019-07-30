#include "HUD.h"
#include "HUDButton.h"
#include "../input/Input.h"
#include "../debug/DebugConsole.h"
#include "../core/Display.h"

// ----------------------------------------------------------------------------
HUD::HUD()
{
}
// ----------------------------------------------------------------------------
HUD::~HUD()
{
	// Cleanup
	for (int i = 0; i < _buttons.size(); ++i)
	{
		delete _buttons[i];
	}
}
// ----------------------------------------------------------------------------
void HUD::update(float _dt)
{
	handleMouseEvents();
}
// ----------------------------------------------------------------------------
void HUD::draw()
{
	for (const HUDButton* b : _buttons)
	{
		b->draw();
	}
}
// ----------------------------------------------------------------------------
GameObject * HUD::clone()
{
	return new HUD();
}
// ----------------------------------------------------------------------------
void HUD::addNewButton(HUDButton* btn)
{
	_buttons.push_back(btn);
}
// ----------------------------------------------------------------------------
void HUD::handleMouseEvents() const
{
	// #TODO Use quad tree or other structure instead of list iteration
	if (Input::getKeyDown(Input::MOUSE_LEFT) && Display::isInFocus())
	{
		sf::Vector2i mousePos = Input::getMousePosition();
		for (HUDButton* btn : _buttons)
		{
			// Bounds check
			sf::Vector2f boundsMin;
			sf::Vector2f boundsMax;
			if (btn->getBounds(&boundsMin, &boundsMax))
			{
				if (mousePos.x > boundsMin.x && mousePos.x < boundsMax.x)
				{
					if (mousePos.y > boundsMin.y && mousePos.y < boundsMax.y)
					{
						btn->onClicked();
					}
				}
			}
		}
	}
}
// ----------------------------------------------------------------------------