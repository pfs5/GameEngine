#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

/**
	Namespace for debuging. Provides printout methods for various objects.
**/
namespace Debug {
	inline void log(const std::string &_s) {
		std::cout << _s << std::endl;
	}

	inline void logError(const std::string &_s) {
		std::cerr << _s << std::endl;
	 }

	inline void log(const char * _s) {
		log(std::string(_s));
	}

	inline void log(const float &_f) {
		log(std::to_string(_f));
	}

	inline void log(const sf::Vector2f &_v) {
		std::string s = "V2f: " + std::to_string(_v.x) + " " + std::to_string(_v.y);
		log(s);
	}

	inline void log(const sf::Vector2u &_v) {
		std::string s = "V2f: " + std::to_string(_v.x) + " " + std::to_string(_v.y);
		log(s);
	}
};