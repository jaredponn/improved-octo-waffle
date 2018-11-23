#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <memory>

#include "components.h"
#include "texturemanager.h"

namespace iow
{

struct TileConfig {
	// constructo ro intialize the std::optionals as empty
	TileConfig(const sf::Texture &texture,
		   std::optional<sf::RectangleShape> col =
			   std::make_optional<sf::RectangleShape>(),
		   std::optional<iow::HP> des = std::make_optional<iow::HP>()

	);

	sf::Sprite sprite; // sprite

	std::optional<sf::RectangleShape> collision; // does have collision?
	std::optional<iow::HP> isDestroyable;	// is it destroyable?
};

using TileConfigs = std::vector<std::unique_ptr<TileConfig>>;
using TileType = size_t;

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

	// for testing if a tile type is valid
	bool isValidTileType(TileType);

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
	void setTileConfig(TileType val, std::unique_ptr<TileConfig> conf);

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
