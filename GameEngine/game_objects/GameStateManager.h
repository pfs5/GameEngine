#pragma once
#include "GameObject.h"
#include "GameState.h"

#include <stack>

/**
	Handles all game state operations including adding and removing.
	Works with a stack mechanism. Also handles object instantiation by delegating 
	to the active state.
**/
class GameStateManager {
	static std::stack<GameState *> m_gameStates;

	static std::vector<std::stack<GameObject*>> m_newObjectsStacks;
	static std::stack<GameObject*> m_destroyedObjects;
public:
	static const int objectLayers = 5;

	// Static methods
	/**
		Instantiate a new GameObject inside the active game state.
		New object get pushed to a stack because adding new object
		while still updating current objects leads to bad behaviour.

		New object should be added by emptying the stack after all
		current objects are done updating.
	**/
	static GameObject * instantiate(GameObject *_gameObject, int _layer = 0);

	/**
		Destroy the game object.
	**/
	static void destroyObject(GameObject * _gameObject);
	
	static GameObject * popNewGameObject(int _layer = 0);
	static GameObject * popDestroyedGameObject();

	static void pushGameState(GameState *_state);
	static void popGameState();
	static GameState * activeGameState();

	// Deleted constructors
public:
	GameStateManager() = delete;
	GameStateManager(const GameStateManager &other) = delete;
};