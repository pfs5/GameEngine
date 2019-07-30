#pragma once
class GameObject;

/**
	Generic game state interface
**/
class GameState {
public:
	virtual ~GameState() {};

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual GameObject * instantiateObject(GameObject  * gameObject) = 0;
	virtual void destroyObject(GameObject * gameObject) = 0;
};
