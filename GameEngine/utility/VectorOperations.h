#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Util.h"

/**
	Basic vector (linear algebra) operations required in the engine.
**/
namespace VectorOperations {
	inline sf::Vector2f memberwiseMultiplication(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return sf::Vector2f{ _v1.x * _v2.x, _v1.y * _v2.y };
	}

	inline float dotProduct(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return  _v1.x * _v2.x + _v1.y * _v2.y;
	}

	inline sf::Vector2f utof(const sf::Vector2u &_v) {
		return sf::Vector2f{ static_cast<float>(_v.x), static_cast<float>(_v.y) };
	}

	// TODO Change to magnitude?
	inline float norm(const sf::Vector2f &_v) {
		return sqrt(powf(_v.x, 2) + powf(_v.y, 2));
	}

	// TODO Change to magnitude?
	inline float squaredNorm(const sf::Vector2f &_v) {
		return powf(_v.x, 2) + powf(_v.y, 2);
	}

	inline float distance(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return norm(_v2 - _v1);
	}

	inline float vectorAngle(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		const float norm_1 = norm(_v1);
		const float norm_2 = norm(_v2);

		// doesn't check zero vectors

		return acosf(dotProduct(_v1, _v2) / norm_1 / norm_2);
	}

	inline sf::Vector2f normalize(const sf::Vector2f &_v)
	{
		sf::Vector2f result;
		float magnitude = norm(_v);

		if (magnitude > 0)
		{
			result.x = _v.x / magnitude;
			result.y = _v.y / magnitude;
		}

		return result;
	}

	inline sf::Vector2f rotate(const sf::Vector2f &_v, float angle)
	{
		float angleRad = Util::degreeToRadian(angle);
		float xRot = _v.x * cos(angleRad) - _v.y * sin(angleRad);
		float yRot = _v.x * sin(angleRad) + _v.y * cos(angleRad);

		return sf::Vector2f{ xRot, yRot };
	}
}