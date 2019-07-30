#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
	Manages all "heavy" external resources for the game and allows easy access by name using the singleton pattern.

	Handles images, fonts, ...
**/
class ResourceManager {
	// Folders
	const std::string RESOURCE_MANAGER_DATA = "../resources/resource_manager.json";
	const std::string FONT_FOLDER = "../resources/fonts/";
	const std::string TEXTURE_FOLDER = "../resources/textures/";
	const std::string AUDIO_FOLDER = "../resources/audio/";
	const std::string RAW_DATA_FOLDER = "../resources/raw_data/";

	const std::map<std::string, sf::Font*> m_fonts = loadFonts();
	const std::map<std::string, sf::Texture*> m_textures = loadTextures();
	const std::map<std::string, sf::SoundBuffer*> m_sounds = loadSounds();
	const std::map<std::string, sf::Music*> m_music = loadMusic();

	const std::string DEFAULT_OBJECT_NAME = "default";

	ResourceManager() {};
public:
	#pragma region Singleton
	static ResourceManager & getInstance() {
		static ResourceManager instance;
		return instance;
	}
	#pragma endregion


	static sf::Font * getFontStatic(const std::string &_fontName) { return getInstance().getFont(_fontName); }
	static sf::Texture * getTextureStatic(const std::string &_textureName) { return getInstance().getTexture(_textureName); }
	static sf::SoundBuffer * getSoundStatic(const std::string &_soundName) { return getInstance().getSound(_soundName); }
	static sf::Music * getMusicStatic(const std::string &_musicName) { return getInstance().getMusic(_musicName); }
	
	static std::string getRawDataPath(const std::string &_dataName) { return ResourceManager::getInstance().RAW_DATA_FOLDER + _dataName; }

	sf::Font * getFont(const std::string &_fontName) const;
	sf::Texture * getTexture(const std::string &_textureName) const;
	sf::SoundBuffer * getSound(const std::string &_soundName) const;
	sf::Music * getMusic(const std::string &_musicName) const;
private:
	std::map<std::string, sf::Font*> loadFonts();
	sf::Font * loadFont(const std::string & _fileName);

	std::map<std::string, sf::Texture*> loadTextures();
	sf::Texture * loadTexture(const std::string & _fileName);

	std::map<std::string, sf::SoundBuffer*> loadSounds();
	sf::SoundBuffer * loadSound(const std::string & _fileName);

	std::map<std::string, sf::Music*> loadMusic();
	sf::Music * loadMusicFile(const std::string & _fileName);
};