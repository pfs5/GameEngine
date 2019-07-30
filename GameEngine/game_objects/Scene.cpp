#include "Scene.h"
#include "GameStateManager.h"
#include "Map.h"
#include "../rendering/Camera.h"
#include "../rendering/Rendering.h"
#include "../physics/PhysicsEngine.h"
#include "../debug/DebugConsole.h"
#include "../ui/HUD.h"

Scene::Scene():
	_map{nullptr},
	_hud{nullptr}
{
	for (int i = 0; i < GameStateManager::objectLayers; ++i)
	{
		_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	setupScene();
}

Scene::~Scene()
{
	for (auto layer : _gameObjects)
	{
		for (GameObject * g : layer)
		{
			delete g;
		}
	}
}

void Scene::update(float dt)
{
	// Map
	if (_map != nullptr)
	{
		_map->update(dt);
	}

	// Update game objects
	for (int i = (int)_gameObjects.size() - 1; i >= 0; --i)
	{
		for (GameObject * g : _gameObjects[i])
		{
			if (g->isActive())
			{
				g->update(dt);
			}
		}
	}

	PhysicsEngine::getInstance().update(dt);

	// HUD
	if (_hud != nullptr)
	{
		_hud->update(dt);
	}

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = (int)_gameObjects.size() - 1; i >= 0; --i)
	{
		while (newObj = GameStateManager::popNewGameObject(i))
		{
			_gameObjects[i].push_back(newObj);
		}
	}

	// Destroy objects
	GameObject * destrObj = nullptr;
	while (destrObj = GameStateManager::popDestroyedGameObject())
	{
		for (auto &layer : _gameObjects)
		{
			layer.erase(std::remove(layer.begin(), layer.end(), destrObj), layer.end());
		}
		delete destrObj;
	}
}

void Scene::draw()
{
	// Map
	if (_map != nullptr)
	{
		_map->draw();
	}

	// Draw game objects
	for (int i = (int)_gameObjects.size() - 1; i >= 0; --i)
	{
		for (GameObject * g : _gameObjects[i])
		{
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	// HUD
	if (_hud != nullptr)
	{
		_hud->draw();
	}

	PhysicsEngine::getInstance().draw();
}

GameObject * Scene::instantiateObject(GameObject * gameObject)
{
	GameObject * newInstance = gameObject->clone();

	return newInstance;
}

void Scene::destroyObject(GameObject * gameObject)
{
	gameObject->setActive(false);
}

void Scene::addGameObjectToScene(GameObject* gameObject, unsigned int layer /*= 0*/)
{
	while (_gameObjects.size() < layer + 1)
	{
		_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	_gameObjects[layer].push_back(gameObject);
}

void Scene::setCurrentMap(Map* map)
{
	// #TODO Delete current map?
	_map = map;
}

void Scene::setHUD(HUD* hud)
{
	if (_hud != nullptr)
	{
		delete _hud;
	}

	_hud = hud;
}

void Scene::setupScene()
{
	// Create console
	DebugConsole* console = DebugConsole::getInstance();
	addGameObjectToScene(console);
}

void Scene::setupDefaultCamera()
{
	Camera* defaultCamera = Rendering::createCamera();
	defaultCamera->setView(Display::getWindow().getDefaultView());

}