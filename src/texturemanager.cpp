#include "texturemanager.h"
#include "logger.h"

void iow::TextureManager::loadTextureFromFile(const iow::TextureName &name,
					      const char *path)
{
	if (m_textures.find(name) != m_textures.end()) {
		Logger::logMessage(
			"ERROR in ResourceManager::loadTextureFromFile. You are loading a texture with the same key as another one. The previous texture will not be overwritten.");
		return;
	}
	m_textures[name].loadFromFile(path);
	m_textures[name].setSmooth(true);
}

const sf::Texture &iow::TextureManager::getTexture(const std::string &key)
{
	auto tmp = m_textures.find(key);

	if (tmp == m_textures.end())
		Logger::logMessage(
			"ERROR in ResourceManager::getTexture. They key you are looking for does not exist. Please ensure that a valid string was entered. Returning whatever value was there, expect buggy behaviour");

	return m_textures[key];
}


const sf::Texture &iow::TextureManager::getTexture(const char *key)
{
	std::string str;
	str.assign(key);

	return getTexture(str);
}
