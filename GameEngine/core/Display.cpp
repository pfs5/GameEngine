#include "Display.h"
#include <memory>
#include <iostream>
#include "../rendering/Rendering.h"
#include "../utility/VectorOperations.h"
#include "../settings/GameSettings.h"

namespace Display {
	std::unique_ptr<sf::RenderWindow> window;
	bool isWindowInFocus = true;

	void init() {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 16;

		std::string title = TITLE + " " +
			"v" + GameSettings::VERSION;

		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), title, sf::Style::Default, settings);
		window->setFramerateLimit(250);
		window->setVerticalSyncEnabled(true);

		window->setPosition(sf::Vector2i{ 100u, 0u });
		window->setMouseCursorVisible(true);
	}

	void clear(const sf::Color& _color) {
		window->clear(_color);
	}

	void display() {
		window->display();
	}

	//void draw(const sf::Drawable& _drawable) {
	//	window->draw(_drawable);
	//}

	void checkWindowEvents() {
		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::KeyPressed) {
				// TODO
			}
			if (e.type == sf::Event::KeyReleased) {
				// TODO
			}
			if (e.type == sf::Event::Closed) {
				window->close();
			}
			if (e.type == sf::Event::GainedFocus) {
				isWindowInFocus = true;
			}
			if (e.type == sf::Event::LostFocus) {
				isWindowInFocus = false;
			}
		}
	}

	bool isOpen() {
		return window->isOpen();
	}

	bool isInFocus() {
		return isWindowInFocus;
	}

	sf::RenderWindow &getWindow() {
		return *window;
	}
	sf::Vector2f worldToScreenPosition(const sf::Vector2f & worldPos)
	{
		if (Rendering::getCameras().empty())
		{
			return sf::Vector2f{};
		}

		// #TODO Add main camera abstraction and use for calculation

		sf::Vector2f viewCenter = Rendering::getCameras()[0]->getView().getCenter();
		sf::Vector2f viewPosition = viewCenter - VectorOperations::utof(getWindow().getSize()) / 2.f;

		return worldPos - viewPosition;
	}
}
