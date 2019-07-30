#include "DebugConsole.h"
#include "../rendering/Rendering.h"
#include "DebugConsoleLogEntry.h"
#include <sstream>
#include <iomanip>
#include "../utility/Util.h"

// ----------------------------------------------------------------------------
DebugConsole* DebugConsole::_instance = nullptr;

// ----------------------------------------------------------------------------
DebugConsole::DebugConsole():
	_isEnabled{true}
{
	initDefaultConsole();
}
// ----------------------------------------------------------------------------
void DebugConsole::initDefaultConsole()
{
	_backgroundShape.setOrigin(sf::Vector2f{ 0.f, 0.f });
	_backgroundShape.setFillColor(sf::Color{ 0, 0, 0, 50 });
	_backgroundShape.setOutlineColor(sf::Color{0, 0, 0, 100});
	_backgroundShape.setOutlineThickness(1.f);

	setPosition(sf::Vector2f{ 0.f, 25.f });
	setSize(sf::Vector2f{ 400.f, (float)Display::HEIGHT });
}
// ----------------------------------------------------------------------------
void DebugConsole::setConsoleEnabled_Internal(bool value)
{
	_isEnabled = value;
}
// ----------------------------------------------------------------------------
void DebugConsole::toggleConsoleEnabled_Internal()
{
	setConsoleEnabled_Internal(!_isEnabled);
}
// ----------------------------------------------------------------------------
void DebugConsole::log_Internal(const std::string& text, LogColor color)
{
	sf::Color logColor;

	switch (color)
	{
		case LogColor::Default:
		{
			logColor = sf::Color{0, 0, 0};
			break;
		}
		case LogColor::Red:
		{
			logColor = sf::Color{ 200, 0, 0 };
			break;
		}
		case LogColor::Yellow:
		{
			logColor = sf::Color{ 200, 200, 0 };
			break;
		}
		case LogColor::Green:
		{
			logColor = sf::Color{ 0, 200, 0 };
			break;
		}
	}

	constructLogEntry(text, logColor);
}
// ----------------------------------------------------------------------------
void DebugConsole::log_Internal(const sf::Vector2f& vector, LogColor color)
{
	std::ostringstream str;
	str << "[Vector2f] x = " << vector.x << " " << vector.y;
	log_Internal(str.str(), color);
}
// ----------------------------------------------------------------------------
void DebugConsole::constructLogEntry(const std::string& str, const sf::Color& color)
{
	// Format output string
	std::ostringstream sStream;
	Util::DateTime datetime = Util::getCurrentTime();
	sStream << "[" << std::setfill('0') << std::setw(2) << datetime.Hours << ":" 
		<< std::setfill('0') << std::setw(2) << datetime.Minutes << ":" 
		<< std::setfill('0') << std::setw(2) << datetime.Seconds << "] " << str;
	std::string fullStr = sStream.str();

	DebugConsoleLogEntry* entry = new DebugConsoleLogEntry(_position + sf::Vector2f{ _margin, _margin }, sf::Vector2f{ _size.x - _margin, _rowHeight });
	entry->setText(fullStr);
	entry->setColor(color);

	// Remove out-of-bounds entries
	while (!_logEntries.empty())
	{
		DebugConsoleLogEntry* e = _logEntries.front();
		float yPos = e->getPosition().y;

		if (yPos - _position.y > 700.f)
		{
			// Remove this instance
			_logEntries.pop_front();
			delete e;
		}
		else
		{
			break;
		}
	}

	for (DebugConsoleLogEntry* e : _logEntries)
	{
		e->setPosition(e->getPosition() + sf::Vector2f{ 0.f, _rowHeight });
	}

	_logEntries.push_back(entry);
}
// ----------------------------------------------------------------------------
DebugConsole* DebugConsole::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new DebugConsole();
	}

	return _instance;
}
// ----------------------------------------------------------------------------
void DebugConsole::setPosition(const sf::Vector2f& position)
{
	_position = position;
	_backgroundShape.setPosition(position + sf::Vector2f{1.f, 1.f});
}
// ----------------------------------------------------------------------------
void DebugConsole::setSize(const sf::Vector2f& size)
{
	_size = size;
	_backgroundShape.setSize(size);
}
// ----------------------------------------------------------------------------
/*override*/
void DebugConsole::update(float _dt)
{
	if (!_isEnabled)
	{
		return;
	}
}
// ----------------------------------------------------------------------------
/*override*/
void DebugConsole::draw()
{
	if (!_isEnabled)
	{
		return;
	}

	Rendering::draw(_backgroundShape);
	for (DebugConsoleLogEntry* e : _logEntries)
	{
		e->draw();
	}
}
// ----------------------------------------------------------------------------
/*override*/
GameObject * DebugConsole::clone()
{
	return new DebugConsole();
}
// ----------------------------------------------------------------------------