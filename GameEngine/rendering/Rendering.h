#pragma once
#include "../core/Display.h"
#include "Camera.h"

class Rendering
{
	friend class Application;
public:
	// Singleton
	static Rendering& getInstance()
	{
		static Rendering instance;
		return instance;
	}

public:
	enum class RenderingLayer : unsigned char
	{
		Layer0 = 1,
		Layer1 = 2,
		Layer2 = 4,
		Layer3 = 8,
		Layer4 = 16,
		Layer5 = 32,
		Layer6 = 64,
		Layer7 = 128
	};

	/**
	 * Clear all render targets. Has to be called before draw(...)
	 */
	static void clear(sf::Color clearColor = sf::Color::Magenta);

	/**
	 * Add drawable object to render queue
	 */
	static void draw(const sf::Drawable& drawable, RenderingLayer renderingLayer = RenderingLayer::Layer0);

	/**
	 * Create new camera and attaching to the rendering pipeline
	 */
	static Camera* createCamera();

	/**
	 * Destroy camera and remove from rendering pipeline
	 */
	static void destroyCamera(Camera *camera);

	/**
	 * Get all active cameras
	 */
	static const std::vector<Camera*>& getCameras();

private:
	std::vector<Camera*> _cameras;
	std::vector<sf::RenderTexture*> _screens;
	sf::Sprite _renderSprite;

private:
	/**
	 * Draw everything in the rendering queue and clear the queue
	 */
	void flushRenderingQueue();
};
