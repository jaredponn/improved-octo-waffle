#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include <vector>

#include "components.h"
#include "texturemanager.h"

namespace iow
{

template <class T>
struct TileCoord {
	T row;
	T col;
};

template <class T>
bool operator==(const iow::TileCoord<T> &a, const iow::TileCoord<T> &b)
{
	return a.row == b.row && a.col == b.col;
}
using TileCoordi = TileCoord<int>;
using TileCoordu = TileCoord<unsigned int>;

struct TileConfig {
	// constructo ro intialize the std::optionals as empty
	TileConfig(const sf::Texture &texture,
		   std::optional<iow::TileCollisionLayer> col,
		   std::optional<iow::HP> des);

	sf::Sprite sprite; // sprite

	std::optional<sf::RectangleShape> collision; // does have collision?
	std::optional<iow::HP> isDestroyable;	// is it destroyable?
};

using TileConfigs = std::vector<std::optional<TileConfig>>;
using TileType = size_t;

class TileMap
{
    private:
	TileConfigs m_tileConfigs;

	iow::TileCoordi m_tileMapDimensions; // number of tiles rows (row) and
					     // columns (col)
	sf::Vector2f m_tileSize;	     // length and width of a tile

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
	void setTileConfig(TileType val, std::optional<TileConfig> conf);

    public:
	/* getters for the world coordinates */
	// gets the tile position and type in world coordinates
	std::pair<iow::Position, iow::TileType> getTile(size_t i) const;
	iow::Position getTileWorldCoord(size_t i) const;
	static iow::Position getTileWorldCoord(iow::TileCoordi const &,
					       sf::Vector2f const &tileSize);
	iow::Position getTileType(size_t i) const;

    public:
	/* getters for the tile maps internal representation of the coords */
	// returns the coordinates fo the tile( e.g. (0,0 is the bottom left))
	iow::TileCoordi getTileCoord(size_t i) const;
	static iow::TileCoordi getTileCoord(size_t i,
					    iow::TileCoordi const &dimensions);

	// inverse of getTileCoord
	size_t getTileIndex(iow::TileCoordi) const;
	static size_t getTileIndex(iow::TileCoordi const &coord,
				   iow::TileCoordi const &dimensions);

    public:
	/* getters extra variables in the tilemap */
	// gets the length ofthe tile map
	size_t getTileMapSize() const;
	// gets the length ofthe tile map
	iow::TileCoordi getTileMapDimensions() const;
	// gets a specific tile config
	const iow::TileConfig getTileConfig(iow::TileType val) const;


	/* printing */
	// TODO not implemented yet
	void printTileMap();
};

/* Using the tile map */
/* TileMap myTileMap;
 myTileMap.setTileSize(100,100);
 myTileMap.loadTileMap(...);

 -----

(0,0)


		(+inf, +inf)


 */

} // namespace iow
