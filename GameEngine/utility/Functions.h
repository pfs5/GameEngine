#pragma once
#include <SFML/System/Vector2.hpp>

namespace Functions
{
	// ----- Functions -----
	class Function
	{
	public:
		virtual ~Function() = default;
		virtual Function* copy() const = 0;
		virtual float value(float in) = 0;
	};

	class LinearFunction : public Function
	{
	public:
		LinearFunction(float k, float l);
		virtual Function* copy() const;
		float value(float in) override;

		static LinearFunction twoPoints(sf::Vector2f p1, sf::Vector2f p2);
	private:
		float _k;
		float _l;
	};
}
