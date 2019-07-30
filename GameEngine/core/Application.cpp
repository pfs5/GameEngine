#include "Application.h"
#include "Display.h"
#include <SFML/System/Clock.hpp>
#include "../game_objects/GameState.h"
#include "../resource_management/ResourceManager.h"
#include "../rendering/Rendering.h"
#include "../game_objects/GameStateManager.h"
#include "../input/Input.h"
#include "../settings/GameSettings.h"
#include "../utility/Util.h"

Application::Application() :
	m_fpsText{"fps: ", *ResourceManager::getInstance().getFont("couriernew1"), 15} {
	Display::init();
 
	// Debug text init
	m_fpsText.setFillColor(sf::Color::Black);
}

Application::~Application() {
}

void Application::runMainLoop() {
	sf::Clock clock;
	sf::Time accumulator;
	sf::Time dt = sf::seconds(1.f / Display::UPS);
	sf::Time max_acc = sf::seconds(0.2f);

	Rendering &rendering = Rendering::getInstance();

	while (Display::isOpen()) {
		Display::checkWindowEvents();
		Display::clear();

		// Exit if stack empty
		if (!GameStateManager::activeGameState()) {
			return;
		}

		// Physics
		accumulator += clock.restart();

		while (accumulator > dt) {
			GameStateManager::activeGameState()->update(dt.asSeconds());
			if (Display::isInFocus()) {
				Input::update();
			}

			accumulator -= dt;
		}

		// Rendering
		GameStateManager::activeGameState()->draw();

		// Debug text 
		sf::Vector2f viewCenter = Display::getWindow().getView().getCenter();
		sf::Vector2u windowSize = Display::getWindow().getSize();
		sf::Vector2f debugTextPos{viewCenter.x - windowSize.x / 2.f + 10.f, viewCenter.y - windowSize.y / 2.f};
		m_fpsText.setPosition(debugTextPos);

		Rendering::draw(m_fpsText);

		calculateFPS(GameSettings::PRINT_FPS);
		rendering.flushRenderingQueue();
		Display::display();
	}
}

void Application::addGameState(GameState * _gameState) {
	GameStateManager::pushGameState(_gameState);
}

void Application::popGameState() {
	GameStateManager::popGameState();
}

void Application::calculateFPS(bool _printFPS) {
	static sf::Clock timer;
	static sf::Clock printTimer;
	static auto numFrames = 0;

	numFrames++;

	if (printTimer.getElapsedTime().asSeconds() >= 1.0f) {
		auto fps = (float)numFrames / timer.getElapsedTime().asSeconds();
		printTimer.restart();
		if (_printFPS) {
			m_fpsText.setString("fps: " + Util::floatToString(fps, 2));
		}

		numFrames = 0;
		timer.restart();
	}
}
