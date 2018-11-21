#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "collision.h"

namespace iow
{

enum class TileType : unsigned int {
	STATIC_WALL,
	DESTROYABLE_WALL,
};

struct TileConfig {
	sf::Texture Texture; // texture
	sf::Sprite sprite;   // sprite

	std::optional<sf::RectangleShape> collision; // does have collision?
	std::optional<bool> isDestroyable;	   // is it destroyable?
};

struct TileMap {
	sf::Vector2f tileMapSize; // number of tiles horizontally and vertically
	sf::Vector2f tileSize;    // length and width of a tile

	// checks if the size is correct
	void assertSize();
};

} // namespace iow
