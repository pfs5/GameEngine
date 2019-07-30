#pragma once
#include <vector>
#include <map>
#include "Animation.h"
#include "AnimationObserver.h"

// #TODO
// REFACTOR THIS CLASS WITH NEW CODING STYLE

/**
	Class servers as a container for animations. Handles animation switching.
	Used by a single object that is to be animated.
**/
class AnimationController : public AnimationObserver {
	const std::string RESOURCE_FOLDER = "../resources/animation_controllers/";
	const std::string EXTENSION = ".animctrl";

	sf::Vector2f _position;
	float _rotation;

	std::vector<Animation*> _animations;
	int _currentAnimation;
	int _nextAnimation;

	bool _isPlaying;

	std::map<std::string, int> _animationIndices;

	std::vector<int> _transitions;
	std::vector<std::map<std::string, int>> _triggerTransitions;

public:
	AnimationController(float _rotation = 0.f);
	~AnimationController();

	void load(std::string _name, bool _play = true);

	// Base engine methods
	void update(float _dt);
	void draw();

	// Controller methods
	void playAnimation(std::string _animation, bool _playInstantly = true);
	//void setAnimationTime(float _time, bool _pause = true);	// #TODO
	void setTrigger(std::string _trigger, bool _playInstantly = true);

	//void play();	// #TODO
	void stop();
	void pause();
	void reset();

	// Animation observer
	virtual void onAnimationEnd() override;

private:
	void playAnimation(int _animation, bool _playInstantly = true);
	bool loadFromFile(std::string _name);
	void playNextAnimation();

#pragma region Getters and setters
public:
	inline sf::Vector2f getPosition() const{ return _position; };
	inline void setPosition(const sf::Vector2f &_pos) 
	{ 
		_position = _pos; 
		for (Animation *a : _animations) 
		{
			a->setPosition(_pos);
		}
	};

	inline bool isPlaying() const { return _isPlaying; };
	inline void setColor(sf::Color _color) 
	{
		for (auto &an : _animations) 
		{
			an->setColor(_color);
		}
	}
	
	inline void setRotation(float _rot) 
	{
		for (auto &an : _animations) 
		{
			an->setRotation(_rot);
		}
	}

	inline void setSize(const sf::Vector2f &size)
	{
		for (auto &an : _animations)
		{
			an->setSize(size);
		}
	}

	inline void setInvertion(const sf::Vector2f &invertion)
	{
		for (auto &an : _animations)
		{
			an->setInvertion(invertion);
		}
	}

	inline void setOrigin(const sf::Vector2f &origin)
	{
		for (auto &an : _animations)
		{
			an->setOrigin(origin);
		}
	}
#pragma endregion

};