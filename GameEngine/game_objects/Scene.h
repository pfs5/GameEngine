#pragma once
#include "GameState.h"
#include <vector>

class HUD;
class Map;

class Scene : public GameState
{
public:
	Scene();
	~Scene();

// GameState
public:
	virtual void update(float dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * gameObject) override;
	virtual void destroyObject(GameObject * gameObject) override;

protected:
	void setupScene();
	void setupDefaultCamera();
	void addGameObjectToScene(GameObject* gameObject, unsigned int layer = 0);
	void setCurrentMap(Map* map);
	void setHUD(HUD* hud);

private:
	std::vector<std::vector<GameObject*>> _gameObjects;
	Map* _map;
	HUD* _hud;
};
