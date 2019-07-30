#pragma once
#include "GameObject.h"
#include "../utility/Functions.h"

class ParticleSystem : public GameObject
{
public:
	class Particle
	{
	public:
		Particle(ParticleSystem* parentSystem, sf::Texture* texture, sf::Vector2f scale = sf::Vector2f{1.f, 1.f});

		void update(float _dt);
		void draw();

		void start(float lifetime);
		void setScale(sf::Vector2f scale);
	public:
		bool isActive = false;

		sf::Vector2f localPosition = sf::Vector2f{0.f, 0.f};
		sf::Vector2f velocity = sf::Vector2f{ 0.f, 0.f };
		sf::Vector2f acceleration = sf::Vector2f{ 0.f, 0.f };

		Functions::Function* alphaInTime;
	private:
		ParticleSystem* _parentSystem;
		float _lifetime;
		float _timer;
		sf::Sprite _sprite;
	};
	
public:
	ParticleSystem(sf::Texture* texture, unsigned int numberOfParticles = 10u, bool burst = false, bool singleShot = false);
	~ParticleSystem();

	// Gameobject
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider * _this, Collider * _other, CollisionData _collisionData ) override;
	GameObject* clone() override;

	void setDestroyTime(float destroyTime);

	// Properties
	void setAlphaInTime(Functions::Function* function);

	void setScale(sf::Vector2f scale);
	void setSpawnRate(float rate);
	void setInitialAcceleration(sf::Vector2f accMin, sf::Vector2f accMax);
	void setInitialAcceleration(sf::Vector2f acc);
	void setInitialVelocity(sf::Vector2f velMin, sf::Vector2f velMax);
	void setInitialVelocity(sf::Vector2f vel);
	void setLifetime(float minLifetime, float maxLifetime);
	void setLifetime(float lifetime);

private:
	sf::Texture* _texture;
	bool _burst;
	bool _singleShot;

	std::vector<Particle> _particles;
	unsigned int _currentParticleIndex;
	float _timer;
	float _particleTimer;

	float _destroyTime;

	Functions::Function* _alphaInTime;

	sf::Vector2f _scale;
	float _spawnPeriod;
	sf::Vector2f _minInitialAcceleration;
	sf::Vector2f _maxInitialAcceleration;
	sf::Vector2f _minInitialVelocity;
	sf::Vector2f _maxInitialVelocity;
	float _minLifetime;
	float _maxLifetime;

private:
	void spawnParticle();
	void spawnAllParticles();
};
