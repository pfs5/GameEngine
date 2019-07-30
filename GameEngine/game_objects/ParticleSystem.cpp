#include "ParticleSystem.h"
#include "GameStateManager.h"
#include "../utility/Util.h"
#include "../rendering/Rendering.h"

// ---- Particle ----
ParticleSystem::Particle::Particle(ParticleSystem* parentSystem, sf::Texture* texture, sf::Vector2f scale) :
	_parentSystem{parentSystem}
{
	_sprite.setTexture(*texture);
	_sprite.setScale(scale);
}

void ParticleSystem::Particle::update(float _dt)
{
	if (!isActive)
	{
		return;
	}

	_lifetime -= _dt;
	_timer += _dt;
	if (_lifetime <= 0.f)
	{
		isActive = false;
	}

	localPosition += 0.5f * acceleration * _dt * _dt + velocity * _dt;
	velocity += acceleration * _dt;
}

void ParticleSystem::Particle::draw()
{
	if (!isActive)
	{
		return;
	}

	if (alphaInTime != nullptr )
	{
		sf::Color color = _sprite.getColor();
		color.a = static_cast<sf::Uint8>(Util::clamp(alphaInTime->value(_timer), 0.f, 1.f) * 255u);
		_sprite.setColor(color);
	}

	_sprite.setPosition(_parentSystem->getGlobalPosition() + localPosition);
	Rendering::draw(_sprite);
}

void ParticleSystem::Particle::start(float lifetime)
{
	_lifetime = lifetime;
	_timer = 0.f;
	localPosition = sf::Vector2f{ 0.f, 0.f };
	isActive = true;
}

void ParticleSystem::Particle::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

// ---- Particle system ----
ParticleSystem::ParticleSystem(sf::Texture* texture, unsigned int numberOfParticles, bool burst, bool singleShot) :
	_texture{texture},
	_burst{burst},	
	_singleShot{singleShot},
	_particles{ numberOfParticles, Particle{this, texture} },
	_currentParticleIndex{0u},
	_timer{0.f},
	_particleTimer{0.f},
	_destroyTime{-1}
{
}

ParticleSystem::~ParticleSystem()
{
	delete _alphaInTime;
}

void ParticleSystem::update(float _dt)
{
	for (Particle& p : _particles)
	{
		p.update(_dt);
	}

	_timer += _dt;

	if (!_singleShot)
	{
		_particleTimer += _dt;
	}

	if (_particleTimer > _spawnPeriod)
	{
		if (_burst)
		{
			spawnAllParticles();
		}
		else
		{
			spawnParticle();
		}

		_particleTimer = 0.f;
	}

	if (_destroyTime > 0.f && _timer > _destroyTime)
	{
		GameStateManager::destroyObject(this);
	}
}

void ParticleSystem::draw()
{
	for (Particle& p : _particles)
	{
		p.draw();
	}
}

void ParticleSystem::onCollision(Collider * _this, Collider * _other, CollisionData _collisionData)
{
}

GameObject* ParticleSystem::clone()
{
	ParticleSystem* newSystem = new ParticleSystem(_texture, (unsigned int)_particles.size(), _burst, _singleShot);
	newSystem->setScale(_scale);
	newSystem->setSpawnRate(1.f / _spawnPeriod);
	newSystem->setInitialAcceleration(_minInitialAcceleration, _maxInitialAcceleration);
	newSystem->setInitialVelocity(_minInitialVelocity, _maxInitialVelocity);
	newSystem->setLifetime(_minLifetime, _maxLifetime);
	newSystem->setAlphaInTime(_alphaInTime->copy());
	newSystem->setDestroyTime(_destroyTime);

	return newSystem;
}

void ParticleSystem::setDestroyTime(float destroyTime)
{
	_destroyTime = destroyTime;
}

void ParticleSystem::setAlphaInTime(Functions::Function* function)
{
	_alphaInTime = function;
}

void ParticleSystem::setScale(sf::Vector2f scale)
{
	_scale = scale;
	for (Particle& p : _particles)
	{
		p.setScale(scale);
	}
}

void ParticleSystem::setSpawnRate(float rate)
{
	_spawnPeriod = 1.f / rate;
	_particleTimer = _spawnPeriod + 1.f;
}

void ParticleSystem::setInitialAcceleration(sf::Vector2f accMin, sf::Vector2f accMax)
{
	_minInitialAcceleration = accMin;
	_maxInitialAcceleration = accMax;
}

void ParticleSystem::setInitialAcceleration(sf::Vector2f acc)
{
	setInitialAcceleration(acc, acc);
}

void ParticleSystem::setInitialVelocity(sf::Vector2f velMin, sf::Vector2f velMax)
{
	_minInitialVelocity = velMin;
	_maxInitialVelocity = velMax;
}

void ParticleSystem::setInitialVelocity(sf::Vector2f vel)
{
	setInitialVelocity(vel, vel);
}

void ParticleSystem::setLifetime(float minLifetime, float maxLifetime)
{
	_minLifetime = minLifetime;
	_maxLifetime = maxLifetime;
}

void ParticleSystem::setLifetime(float lifetime)
{
	setLifetime(lifetime, lifetime);
}

void ParticleSystem::spawnParticle()
{
	Particle& newPart = _particles[_currentParticleIndex];

	newPart.acceleration = Util::randomVector2f(_minInitialAcceleration, _maxInitialAcceleration);
	newPart.velocity = Util::randomVector2f(_minInitialVelocity, _maxInitialVelocity);
	newPart.alphaInTime = _alphaInTime;
	newPart.start(Util::randomFloat(_minLifetime, _maxLifetime));

	_currentParticleIndex = (_currentParticleIndex + 1) % _particles.size();
}

void ParticleSystem::spawnAllParticles()
{
	for (unsigned int i=0; i < _particles.size(); ++i)
	{
		spawnParticle();
	}
}
