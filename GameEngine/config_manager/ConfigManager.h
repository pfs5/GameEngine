#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

/*
	Manages the config file. Use this to change settings in the game without recompiling.
	Support:
		string	- all values are stored as a string and can be retreived as a string
		int		- tries to parse the string to int, NOTICE: will parse floats as int
		float	- tries to parse the string to float
		bool	- tries to parse the string to bool, 'True','true' will return true, everything else will return false
		Vector3 - tries to parse the string to Vector3f, x, y and z components must be separated by space e.g. "1.2 -1.3 1.4"

	Usage: ConfigManager::getInstance().getInt("game", "key2")
*/
class ConfigManager {

	const std::string CONFIG_FILE_PATH = "../resources/configs/config.json";

	const std::map<std::string, std::map<std::string, std::string>> m_config = loadConfig();

private:
	ConfigManager() {};
	std::map<std::string, std::map<std::string, std::string>> loadConfig();
	bool isSectionAndKeyValid(std::string section, std::string key);

public:
	#pragma region Singleton
	static ConfigManager & getInstance() {
		static ConfigManager instance;
		return instance;
	}
	#pragma endregion

	std::string getString(std::string section, std::string key, std::string defaultValue = "");
	int getInt(std::string section, std::string key, int defaultValue = 0);
	float getFloat(std::string section, std::string key, float defaultValue = 0.f);
	bool getBool(std::string section, std::string key, bool defaultValue = false);
	sf::Vector2f getVector2(std::string section, std::string key, sf::Vector2f defaultValue = sf::Vector2f(0.f, 0.f));
	sf::Vector3f getVector3(std::string section, std::string key, sf::Vector3f defaultValue = sf::Vector3f(0.f, 0.f, 0.f));
};

