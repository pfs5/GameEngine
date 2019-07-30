#include "AnimationController.h"
#include <fstream>
#include <sstream>
#include "../utility/json.h"
#include "../debug/Debug.h"

AnimationController::AnimationController(float _rotation) : 
	_rotation(_rotation), _currentAnimation (0), _nextAnimation(0), _isPlaying(false) {
}

AnimationController::~AnimationController() {
}

void AnimationController::load(std::string _name, bool _play) {
	if (!loadFromFile(_name)) {
		Debug::logError("[AnimationController] Error loading " + _name);
	}

	if (_animations.size() <= _currentAnimation) {
		return;
	}

	_isPlaying = _play;

	if (_play) {
		_animations[_currentAnimation]->play();
	}
	else {
		_animations[_currentAnimation]->stop();
	}
}

void AnimationController::update(float _dt) {
	if (_isPlaying) {
		_animations[_currentAnimation]->update(_dt);
	}
}

void AnimationController::draw() {
	_animations[_currentAnimation]->draw();
}

void AnimationController::playAnimation(std::string _animation, bool _playInstantly) {
	int animationIndex = _animationIndices.at(_animation);
	playAnimation(animationIndex, _playInstantly);
}

// #TODO
//void AnimationController::setAnimationTime(float _time, bool _pause) {
//	m_animations[m_currentAnimation]->setTime(_time, _pause);
//}

void AnimationController::setTrigger(std::string _trigger, bool _playInstantly) {
	try {
		int nextAnimation = _triggerTransitions[_currentAnimation].at(_trigger);
		playAnimation(nextAnimation, _playInstantly);

		_isPlaying = true;
	} catch (std::out_of_range) {
		return;
	}
}

void AnimationController::stop() {
	pause();
	reset();
}

void AnimationController::pause() {
	_isPlaying = false;
}

void AnimationController::reset() {
	// TODO
}

void AnimationController::playAnimation(int _animation, bool _playInstantly) {
	try {
		_nextAnimation = _animation;
		if (_playInstantly) {
			playNextAnimation();
		}
		_isPlaying = true;
	} catch (std::out_of_range e) {
		return;
	}
}

bool AnimationController::loadFromFile(std::string _name) {
	std::string path = RESOURCE_FOLDER + _name + EXTENSION;
	std::ifstream file{ path };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;

		// Animations
		for (auto &a : data["animations"]) {
			std::string name = a["name"];
			bool isLooping = a["islooping"] == "true";
			std::string speed = a["speed"];

			Animation *anim = new Animation(name);
			
			anim->setRotation(_rotation);
			anim->setSpeed(std::stof(speed));
			anim->setIsLooping(isLooping);

			_animations.push_back(anim);
			_transitions.push_back(-1);
			_triggerTransitions.emplace_back();		// #TODO CHECK

			anim->attachObserver(this);

			_animationIndices.emplace(name, _animations.size() - 1);
		}

		// Transitions
		for (auto &t : data["transitions"]) {
			std::string trigger = t["trigger"];
			std::string from = t["from"];
			std::string to = t["to"];

			int fromIndex = _animationIndices[from];
			int toIndex = _animationIndices[to];

			if (trigger == "default") {
				_transitions[fromIndex] = toIndex;
			} else {
				_triggerTransitions[fromIndex].emplace(trigger, toIndex);
			}
		}

		file.close();
		return true;
	}
	
	return false;
}

void AnimationController::playNextAnimation() {
	_animations[_currentAnimation]->stop();
	_currentAnimation = _nextAnimation;
	_animations[_currentAnimation]->play();

	if (_transitions[_currentAnimation] != -1) {
		_nextAnimation = _transitions[_currentAnimation];
	}
}

void AnimationController::onAnimationEnd() {
	// Switch to next animation
	if (_nextAnimation != _currentAnimation || _animations[_currentAnimation]->isLooping()) {
		playNextAnimation();
	}
	else {
		_isPlaying = false;
	}
}
