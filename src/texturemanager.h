#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

namespace iow
{

using TextureName = std::string;
class TextureManager
{

    public:
	std::unordered_map<iow::TextureName, sf::Texture> m_textures;

	// loads a texture fomr a file. If the texture already exists, it will
	// not oevrewrite it and log a message telling you that.
	void loadTextureFromFile(const iow::TextureName &name,
				 const char *path);
	// gets the texture from the key. If it does not exist, it'll log
	// somthing at the screen and return a weird buggy texture that will
	// most likely segfault
	const sf::Texture &getTexture(const std::string &key);
	const sf::Texture &getTexture(const char *key);
};
} // namespace iow
