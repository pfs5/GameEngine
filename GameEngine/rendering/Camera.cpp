#include "Camera.h"

void Camera::setLayerMask(unsigned char mask)
{
	_layerMask = mask;
}

unsigned char Camera::getLayerMask() const
{
	return _layerMask;
}

void Camera::setView(const sf::View& value)
{
	_view = value;
}

const sf::View& Camera::getView() const
{
	return _view;
}

void Camera::setColorTint(const sf::Color & value)
{
	_colorTint = value;
}

const sf::Color & Camera::getColorTint() const
{
	return _colorTint;
}

void Camera::setLocalPosition(const sf::Vector2f& _pos)
{
	ITransformable::setLocalPosition(_pos);

	_view.setCenter(_globalPosition);
}

Camera::Camera() :
	_layerMask{ 0b11111111 },
	_colorTint{ sf::Color{255, 255, 255, 255} }
{
}
