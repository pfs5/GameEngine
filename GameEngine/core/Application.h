#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

/**
	Main application class holding the whole game and game loop.
**/
class Application {
	sf::Text m_fpsText;
public:
	Application();
	~Application();

	/**
		Runs the main game loop
	**/
	void runMainLoop();

	/**
		Adds a game state to the application
		@param _gameState pointer to gamestate allocated on dynamic storage.
		Application handles memory deallocation.
	**/
	void addGameState(GameState *_gameState);

	/**
		Removes the last game state and switches to the previous one.
	**/
	void popGameState();

private:
	void calculateFPS(bool _printFPS = false);
};