#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Color.hpp>
#include "../game_objects/ITransformable.h"

class Camera : public ITransformable
{
	friend class Rendering;

public:
	void setLayerMask(unsigned char value);
	unsigned char getLayerMask() const;

	void setView(const sf::View& value);
	const sf::View& getView() const;

	void setColorTint(const sf::Color& value);
	const sf::Color& getColorTint() const;

// ITransformable
public:
	void setLocalPosition(const sf::Vector2f& _pos) override;

private:
	Camera();
	~Camera() = default;

private:
	unsigned char _layerMask;
	sf::View _view;
	sf::Color _colorTint;
};
