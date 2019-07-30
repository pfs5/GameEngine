#include "ResourceManager.h"
#include "../utility/json.h"
#include "../debug/Debug.h"
#include <fstream>

sf::Font * ResourceManager::getFont(const std::string &_fontName) const {
	try {
		return m_fonts.at(_fontName);
	} catch (std::out_of_range e) {
		return nullptr;
	}
}

sf::Texture * ResourceManager::getTexture(const std::string &_textureName) const {
	try {
		return m_textures.at(_textureName);
	} catch (std::out_of_range e) {
		try {
			return m_textures.at(DEFAULT_OBJECT_NAME);
		}
		catch (std::out_of_range e) {
			return nullptr;
		}
	}
}

sf::SoundBuffer * ResourceManager::getSound(const std::string &_soundName) const {
	try {
		return m_sounds.at(_soundName);
	}
	catch (std::out_of_range e) {
		return nullptr;
	}
}

sf::Music * ResourceManager::getMusic(const std::string &_musicName) const {
	try {
		return m_music.at(_musicName);
	}
	catch (std::out_of_range e) {
		return nullptr;
	}
}

std::map<std::string, sf::Font*> ResourceManager::loadFonts() {
	std::map<std::string, sf::Font*> fonts;

	// Load fonts
	std::ifstream file{ RESOURCE_MANAGER_DATA };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		for (auto font : data["fonts"]) {
			fonts.emplace(font["name"], loadFont(font["path"]));
		}

		file.close();
	}

	return fonts;
}

sf::Font * ResourceManager::loadFont(const std::string & _fileName) {
	sf::Font * f = new sf::Font();
	if (!f->loadFromFile(FONT_FOLDER + _fileName)) {
		Debug::logError("Error loading font " + _fileName);
	}

	return f;
}

std::map<std::string, sf::Texture*> ResourceManager::loadTextures() {
	std::map<std::string, sf::Texture*> textures;

	// Load textures
	std::ifstream file{ RESOURCE_MANAGER_DATA };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		for (auto tex : data["textures"]) {
			textures.emplace(tex["name"], loadTexture(tex["path"]));
		}

		file.close();
	}

	return textures;
}

sf::Texture * ResourceManager::loadTexture(const std::string & _fileName) {
	sf::Texture * t = new sf::Texture();
	if (!t->loadFromFile(TEXTURE_FOLDER + _fileName)) {
		Debug::logError("Error loading texture " + _fileName);
	}

	return t;
}

std::map<std::string, sf::SoundBuffer*> ResourceManager::loadSounds() {
	std::map<std::string, sf::SoundBuffer*> sounds;

	// Load sounds
	std::ifstream file{ RESOURCE_MANAGER_DATA };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		for (auto sound : data["sounds"]) {
			sounds.emplace(sound["name"], loadSound(sound["path"]));
		}

		file.close();
	}

	return sounds;
}

sf::SoundBuffer * ResourceManager::loadSound(const std::string & _fileName) {
	sf::SoundBuffer * b = new sf::SoundBuffer();
	if (!b->loadFromFile(AUDIO_FOLDER + _fileName)) {
		Debug::logError("Error load audio " + _fileName);
	}

	return b;
}

std::map<std::string, sf::Music*> ResourceManager::loadMusic() {
	std::map<std::string, sf::Music*> music;

	// Load sounds
	std::ifstream file{ RESOURCE_MANAGER_DATA };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		for (auto sound : data["music"]) {
			music.emplace(sound["name"], loadMusicFile(sound["path"]));
		}

		file.close();
	}

	return music;
}

sf::Music * ResourceManager::loadMusicFile(const std::string & _fileName) {
	sf::Music * m = new sf::Music();
	if (!m->openFromFile(AUDIO_FOLDER + _fileName)) {
		Debug::logError("Error load audio " + _fileName);
	}

	return m;
}
