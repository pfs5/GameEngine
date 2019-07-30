#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class AnimationObserver;

class Animation
{
public:
	Animation(const std::string &name);

	void update(float _dt);
	void draw();

	void setSpeed(float speed);
	void setSize(const sf::Vector2f &size);
	void setColor(const sf::Color &color);
	void setPosition(const sf::Vector2f &position);
	void setRotation(float rotation);
	bool isLooping() const;
	void setIsLooping(bool value);
	void setInvertion(const sf::Vector2f &inv);
	void setOrigin(const sf::Vector2f& origin);

	// Control
	void play();
	void stop();
	void pause();

	// Observers
	void attachObserver(AnimationObserver *_o);
	void dettachObserver(AnimationObserver *_o);

private:
	std::string _name;
	sf::Texture * _spritesheet;
	unsigned int _rows;
	unsigned int _cols;
	std::vector<float> _frameTimes;
	float _speed;
	bool _looping;
	sf::Vector2f _invertion;

	// Visual
	sf::Sprite _sprite;

	// Sprite frame data
	float _frameWidth;
	float _frameHeight;

	// Animation data
	unsigned int _currentFrame;
	float _timer;

	// Play state
	bool _isPlaying;

	std::vector<AnimationObserver*> _observers;


private:
	void loadAnimation(const std::string &path);
	void setCurrentFrame();
	void reset();
	void notifyOnAnimationEnd();
};
