#pragma once
#include "../game_objects/GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <deque>
#include "SFML/Graphics/Color.hpp"

// ----------------------------------------------------------------------------
class DebugConsoleLogEntry;

// ----------------------------------------------------------------------------
enum class LogColor
{
	Default,
	Red,
	Yellow,
	Green
};
// ----------------------------------------------------------------------------
class DebugConsole : public GameObject {
	GAME_OBJECT_BODY()

// Static interface
public:
	static DebugConsole* getInstance();
	static inline void setConsoleEnabled(bool value) { getInstance()->setConsoleEnabled(value); }
	static inline void toggleConsoleEnabled() { getInstance()->toggleConsoleEnabled_Internal(); }
	static inline void log(const char* text, LogColor color = LogColor::Default) { getInstance()->log_Internal(std::string(text), color); }
	static inline void log(const std::string& text, LogColor color = LogColor::Default) { getInstance()->log_Internal(text, color); }
	static inline void log(const sf::Vector2f& vector, LogColor color = LogColor::Default) { getInstance()->log_Internal(vector, color); }

public:
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);

// GameObject
public:
	virtual void update(float _dt) override;

	virtual void draw() override;

	virtual GameObject * clone() override;

private:
	static DebugConsole* _instance;

	sf::Vector2f _position;
	sf::Vector2f _size;

	bool _isEnabled;

	std::deque<DebugConsoleLogEntry*> _logEntries;

	// --- Visuals ---
	sf::RectangleShape _backgroundShape;
	float _rowHeight = 20.f;
	float _margin = 5.f;

private:
	// --- Private constructors ---
	DebugConsole();
	DebugConsole(const DebugConsole& other)		= delete;
	void operator= (const DebugConsole& other)	= delete;

	void initDefaultConsole();
	void setConsoleEnabled_Internal(bool value);
	void toggleConsoleEnabled_Internal();
	void log_Internal(const std::string& text, LogColor color);
	void log_Internal(const sf::Vector2f& vector, LogColor color);

	void constructLogEntry(const std::string& str, const sf::Color& color);
};
// ----------------------------------------------------------------------------