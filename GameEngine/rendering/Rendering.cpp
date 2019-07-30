#include "Rendering.h"

#include <algorithm>

void Rendering::clear(sf::Color clearColor)
{
	auto &screens = getInstance()._screens;

	Display::getWindow().clear(clearColor);
	for (auto &screen : screens)
	{
		screen->clear(sf::Color::Transparent);
	}
}

void Rendering::draw(const sf::Drawable & drawable, RenderingLayer renderingLayer)
{
	auto &cameras = getInstance()._cameras;
	auto &screens = getInstance()._screens;
	sf::RenderWindow &window = Display::getWindow();

	// Draw first camera directly to window
	if (!cameras.empty() && cameras[0]->getLayerMask() & static_cast<unsigned int>(renderingLayer))
	{
		window.setView(cameras[0]->getView());
		window.draw(drawable);
	}

	// Draw other cameras to off-screen textures
	for (unsigned int i = 1; i < cameras.size(); ++i)
	{
		if (cameras[i]->getLayerMask() & static_cast<unsigned int>(renderingLayer))
		{
			screens[i - 1]->setView(cameras[i]->getView());
			screens[i - 1]->draw(drawable);
		}
	}
}

Camera * Rendering::createCamera()
{
	auto &cameras = getInstance()._cameras;
	auto &screens = getInstance()._screens;
	sf::RenderWindow &window = Display::getWindow();

	Camera* newCamera = new Camera();
	cameras.push_back(newCamera);

	if (cameras.size() > 1)
	{
		auto *screen = new sf::RenderTexture{};
		screen->create(window.getSize().x, window.getSize().y);
		screens.push_back(screen);
	}

	return newCamera;
}

void Rendering::destroyCamera(Camera* camera)
{
	auto &cameras = getInstance()._cameras;
	auto &screens = getInstance()._screens;

	unsigned int camIndex = -1;
	for (camIndex = 0; camIndex < cameras.size(); ++camIndex)
	{
		if (cameras[camIndex] == camera)
		{
			delete cameras[camIndex];
			break;
		}
	}
	
	cameras.erase(std::remove(cameras.begin(), cameras.end(), camera), cameras.end());
	screens.erase(screens.begin() + camIndex);
}

const std::vector<Camera*>& Rendering::getCameras()
{
	return getInstance()._cameras;
}

void Rendering::flushRenderingQueue()
{
	auto &screens = getInstance()._screens;
	auto &cameras = getInstance()._cameras;
	sf::RenderWindow &window = Display::getWindow();

	window.setView(window.getDefaultView());

	for (unsigned int i=0; i < screens.size(); ++i)
	{
		screens[i]->display();
		_renderSprite.setTexture(screens[i]->getTexture());
		_renderSprite.setColor(cameras[i + 1]->getColorTint());
		window.draw(_renderSprite);
	}
}
