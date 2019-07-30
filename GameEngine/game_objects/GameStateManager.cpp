#include "GameStateManager.h"

std::stack<GameState *> GameStateManager::m_gameStates;
std::vector<std::stack<GameObject*>> GameStateManager::m_newObjectsStacks(objectLayers);
std::stack<GameObject *> GameStateManager::m_destroyedObjects;


GameObject * GameStateManager::instantiate(GameObject * _gameObject, int _layer) {
	GameObject * o =  activeGameState()->instantiateObject(_gameObject);
	m_newObjectsStacks[_layer].push(o);

	return o;
}

void GameStateManager::destroyObject(GameObject * _gameObject) {
	activeGameState()->destroyObject(_gameObject);
	m_destroyedObjects.push(_gameObject);
}

GameObject * GameStateManager::popNewGameObject(int _layer) {
	if (m_newObjectsStacks[_layer].empty()) {
		return nullptr;
	}

	GameObject * o = m_newObjectsStacks[_layer].top();
	m_newObjectsStacks[_layer].pop();
	return o;
}

GameObject * GameStateManager::popDestroyedGameObject() {
	if (m_destroyedObjects.empty()) {
		return nullptr;
	}

	GameObject * o = m_destroyedObjects.top();
	m_destroyedObjects.pop();
	return o;
}

void GameStateManager::pushGameState(GameState * _state) {
	m_gameStates.push(_state);
}

void GameStateManager::popGameState() {
	delete m_gameStates.top();
	m_gameStates.pop();
}

GameState * GameStateManager::activeGameState() {
	if (m_gameStates.empty()) {
		return nullptr;
	}
	return m_gameStates.top();
}
