#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <utility>

#include "components.h"

namespace iow
{

enum class TileType : size_t {
	GROUND = 0,
	STATIC_WALL = 1,
	DESTROYABLE_WALL,

	TOTAL_NUMBER_OF_TILES // should not be used when getting tile configs
};

static inline bool isValidTileType(size_t n)
{
	for (size_t i = 0;
	     i < static_cast<size_t>(iow::TileType::TOTAL_NUMBER_OF_TILES);
	     ++i) {
		if (n == i) {
			return true;
		}
	}
	return false;
}

struct TileConfig {
	// constructo ro intialize the std::optionals as empty
	TileConfig();

	sf::Texture texture; // texture
	sf::Sprite sprite;   // sprite

	std::optional<sf::RectangleShape> collision; // does have collision?
	std::optional<iow::HP> isDestroyable;	// is it destroyable?
};

using TileConfigs =
	std::array<TileConfig,
		   static_cast<size_t>(iow::TileType::TOTAL_NUMBER_OF_TILES)>;

class TileMap
{
    private:
	TileConfigs m_tileConfigs;
	sf::Vector2u m_tileMapSize; // number of tiles rows (x) and columns (y)
	sf::Vector2f m_tileSize;    // length and width of a tile

	std::vector<iow::TileType> m_tiles;

	// loads tile map from a vector of space seperated strings in a vector
	void loadTileMap(std::vector<std::string> tilemap);

	// used for checking if the dimensions line up with the tile map.  Tile
	// must be rectangles
	void assertTileMapSize();

	// gets the tile size
	const sf::Vector2f &getTileSize();

    public:
	TileMap();

	/* setters */
	// loads a tile map from a space seperated string for columns, and \n
	// seperated string for the rows
	void loadTileMap(const std::string &tilemap);
	void loadTileMap(const char[]);

	// sets the size of the tiles (e.g.100x100)
	void setTileSize(const sf::Vector2f &);
	void setTileSize(const float x, const float y);

	// set the tile config. witha given path to a texture
	void setTileConfig(const char *, const TileType);

	/* getters */
	std::pair<iow::Position, iow::TileType> getTile(size_t i);
	// gets the length ofthe tile map
	size_t getTileMapSize();
	// gets a specific tile config
	const iow::TileConfig getTileConfig(iow::TileType val);

	/* printing */
	// TODO not implemented yet
	void printTileMap();
};

/* Using the tile map */
/* TileMap myTileMap; */
/* myTileMap.setTileSize(100,100); */
/* myTileMap.loadTileMap(...); */

} // namespace iow
