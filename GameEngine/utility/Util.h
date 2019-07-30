#pragma once
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

#define PI 3.14159265359f

#include <SFML/Graphics.hpp>

namespace Util {
	static bool isInitialized = false;
	
	/**
		Random float in [0, 1] range
	**/
	inline float randomFloat() {
		if (!isInitialized) {
			srand(static_cast<unsigned int>(time(nullptr)));
			isInitialized = true;
		}

		return static_cast<float>(rand()) / RAND_MAX;
	}

	/**
		Random float in [minValue, maxValue] range
	**/
	inline float randomFloat(float minValue, float maxValue)
	{
		return minValue + (maxValue - minValue) * randomFloat();
	}

	inline sf::Vector2f randomVector2f(sf::Vector2f minValue, sf::Vector2f maxValue)
	{
		return sf::Vector2f 
		{
			randomFloat(minValue.x, maxValue.x),
			randomFloat(minValue.y, maxValue.y),
		};
	}

	/**
		Random integer in [_min, _max] range
	**/
	inline int randomInt(int _min, int _max) {
		if (!isInitialized) {
			srand(static_cast<unsigned int>(time(nullptr)));
			isInitialized = true;
		}

		float num = _min + (_max - _min) * randomFloat();

		return static_cast<int>(roundf(num));
	}

	inline std::string floatToString(const float &_f, const int &_digits) {
		std::stringstream sstream;
		sstream << std::fixed << std::setprecision(_digits) << _f;
		return sstream.str();
	}

	inline float radianToDegree(const float &_radians) {
		return _radians * 180.f / PI;
	}

	inline float degreeToRadian(const float &_degrees)
	{
		return _degrees * PI / 180;
	}

	template <class T>
	inline int randomFromVector(std::vector<T> vector)
	{
		return randomInt(0, vector.size() - 1);
	}

	template<class T>
	inline T clamp(T value, T minValue, T maxValue)
	{
		return std::min(maxValue, std::max(minValue, value));
	}

	struct DateTime
	{
		int Seconds;
		int Minutes;
		int Hours;
		int Day;
		int Month;
		int Year;
	};

	inline DateTime getCurrentTime()
	{
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm timeStruct;
		localtime_s(&timeStruct, &now);

		DateTime dt;
		dt.Seconds = timeStruct.tm_sec;
		dt.Minutes = timeStruct.tm_min;
		dt.Hours = timeStruct.tm_hour;
		dt.Day = timeStruct.tm_mday;
		dt.Month = timeStruct.tm_mon;
		dt.Year = timeStruct.tm_year;

		return dt;
	}
}