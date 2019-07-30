#include "ConfigManager.h"
#include <fstream>
#include <iostream>
#include <locale>
#include "../utility/json.h"

const std::string CONFIG_KEY	= "config";
const std::string SECTION_KEY	= "section";
const std::string ENTRIES_KEY	= "entries";
const std::string KEY_KEY		= "key";
const std::string VALUE_KEY		= "value";

std::map<std::string, std::map<std::string, std::string>> ConfigManager::loadConfig()
{
	std::map<std::string, std::map<std::string, std::string>> config;

	std::ifstream file{ CONFIG_FILE_PATH };
	if (file.is_open())
	{
		nlohmann::json data;
		file >> data;

		for (auto section : data[CONFIG_KEY])
		{
			std::map<std::string, std::string> sectionData;
			for (auto entry : section[ENTRIES_KEY])
			{
				sectionData.emplace(entry[KEY_KEY], entry[VALUE_KEY]);
			}

			//std::cout << "Read section of length: " << sectionData.size() << std::endl;

			config.emplace(section[SECTION_KEY], sectionData);
		}

		//std::cout << "Read config of section count: " << config.size() << std::endl;
	}

	return config;
}

bool ConfigManager::isSectionAndKeyValid(std::string section, std::string key)
{
	if (m_config.find(section) == m_config.end())
	{
		std::cerr << "Unable to find section [" << section << "]" << std::endl;
		return false;
	}

	if (m_config.at(section).find(key) == m_config.at(section).end())
	{
		std::cerr << "Unable to find key [" << key << "] in section [" << section << "]" << std::endl;
		return false;
	}

	return true;
}

// Returns string value from config
std::string ConfigManager::getString(std::string section, std::string key, std::string defaultValue)
{
	if (isSectionAndKeyValid(section, key))
	{
		return m_config.at(section).at(key);
	}
	
	return defaultValue;
}

// Returns int value from config - returns defaultValue if requested value isn't a valid int
int ConfigManager::getInt(std::string section, std::string key, int defaultValue)
{
	if (isSectionAndKeyValid(section, key))
	{
		std::string value = m_config.at(section).at(key);

		try 
		{
			return std::stoi(value);
		}
		catch (std::invalid_argument e)
		{
			std::cerr << "[" << value << "] is not a valid int";
		}
		catch (std::out_of_range e)
		{
			std::cerr << "[" << value << "] is to large for int";
		}
	}

	return defaultValue;
}

// Returns float value from config - returns defaultValue if requested value isn't a valid float
float ConfigManager::getFloat(std::string section, std::string key, float defaultValue)
{
	if (isSectionAndKeyValid(section, key))
	{
		std::string value = m_config.at(section).at(key);

		try
		{
			return std::stof(value);
		}
		catch (std::invalid_argument e)
		{
			std::cerr << "[" << value << "] is not a valid float";
		}
		catch (std::out_of_range e)
		{
			std::cerr << "[" << value << "] is to large for float";
		}
	}

	return defaultValue;
}

// Return bool from config - return true if value is 'true' or 'True', false otherwise
bool ConfigManager::getBool(std::string section, std::string key, bool defaultValue)
{
	if (isSectionAndKeyValid(section, key))
	{
		std::string value = m_config.at(section).at(key);

		// change string value to lowercase
		std::locale loc;
		for (std::string::size_type i = 0; i < value.length(); ++i)
		{
			value[i] = std::tolower(value[i], loc);
		}

		return value == "true";
	}

	return defaultValue;
}

sf::Vector2f ConfigManager::getVector2(std::string section, std::string key, sf::Vector2f defaultValue)
{
	if (isSectionAndKeyValid(section, key))
	{
		std::string value = m_config.at(section).at(key);
		char delimiter = ' ';

		// Split string into 2 components separated by delimiter
		std::vector<std::string> vectorComponents;		
		std::size_t foundDelimiter = value.find(delimiter);
		if (foundDelimiter == std::string::npos)
		{
			std::cerr << "Invalid format for Vector2";
			return defaultValue;
		}
		vectorComponents.push_back(value.substr(0, foundDelimiter));
		value = value.substr(foundDelimiter + 1, value.length() - foundDelimiter);		
		vectorComponents.push_back(value);

		// Try to convert the components into a valid vector
		sf::Vector2f result;
		try
		{
			result.x = std::stof(vectorComponents[0]);
			result.y = std::stof(vectorComponents[1]);

			return result;
		}
		catch (std::invalid_argument e)
		{
			std::cerr << "[" << value << "] is not a valid float";
		}
		catch (std::out_of_range e)
		{
			std::cerr << "[" << value << "] is to large for float";
		}
	}

	return defaultValue;
}

sf::Vector3f ConfigManager::getVector3(std::string section, std::string key, sf::Vector3f defaultValue)
{
	if (isSectionAndKeyValid(section, key))
	{
		std::string value = m_config.at(section).at(key);
		char delimiter = ' ';

		// Split string into 3 components separated by delimiter
		std::vector<std::string> vectorComponents;
		for (int i = 0; i < 2; ++i)
		{
			std::size_t foundDelimiter = value.find(delimiter);
			if (foundDelimiter == std::string::npos)
			{
				std::cerr << "Invalid format for Vector3";
				return defaultValue;
			}

			vectorComponents.push_back(value.substr(0, foundDelimiter));
			value = value.substr(foundDelimiter+1, value.length() - foundDelimiter);
		}
		vectorComponents.push_back(value);
	
		// Try to convert the components into a valid vector
		sf::Vector3f result;
		try
		{
			result.x = std::stof(vectorComponents[0]);
			result.y = std::stof(vectorComponents[1]);
			result.z = std::stof(vectorComponents[2]);

			return result;
		}
		catch (std::invalid_argument e)
		{
			std::cerr << "[" << value << "] is not a valid float";
		}
		catch (std::out_of_range e)
		{
			std::cerr << "[" << value << "] is to large for float";
		}
	}

	return defaultValue;
}
