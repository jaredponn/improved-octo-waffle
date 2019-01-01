#include <string>

#include "logger.h"
#include "tilemap.h"
#include "util.h"


constexpr float DEFAULT_TILE_SIZE = 100;


iow::TileConfig::TileConfig(const sf::Texture &texture,
			    std::optional<iow::TileCollisionLayer> col,
			    std::optional<iow::HP> des)
{
	sprite.setTexture(texture);

	collision = col;
	isDestroyable = des;
}

iow::TileMap::TileMap(){};

void iow::TileMap::assertTileMapSize()
{
	if (m_tileMapSize.y * m_tileMapSize.x != m_tiles.size())
		Logger::logMessage(
			"ERROR with tile map config -- the width and the height of the tilemap must be the same as the .size() aof the tiles vector.");
}

void iow::TileMap::setTileSize(const sf::Vector2f &n)
{
	sf::Vector2f tmp;
	if (n.x <= 0) {
		Logger::logMessage(
			"ERROR setting tile horizontal width of the tile size. Please input a tile size greater than 0.using default value of:");
		Logger::logMessage(std::to_string(DEFAULT_TILE_SIZE).c_str());
		tmp.x = DEFAULT_TILE_SIZE;
	} else {
		tmp.x = n.x;
	}

	if (n.y <= 0) {
		Logger::logMessage(
			"ERROR setting tile vertical width of the tile size. Please input a tile size greater than 0.using default value of:");
		Logger::logMessage(std::to_string(DEFAULT_TILE_SIZE).c_str());
		tmp.y = DEFAULT_TILE_SIZE;
	} else {
		tmp.y = n.y;
	}

	m_tileSize = tmp;
}

void iow::TileMap::setTileSize(const float x, const float y)
{
	setTileSize(sf::Vector2f(x, y));
}

const sf::Vector2f &iow::TileMap::getTileSize()
{
	return m_tileSize;
}


void iow::TileMap::loadTileMap(const char tilemap[])
{
	if (tilemap != nullptr)
		loadTileMap(std::string(tilemap));
	else {
		Logger::logMessage(
			"ERROR in loadTileMap. Ensure that the string is not NULL.");
	}
}

void iow::TileMap::loadTileMap(const std::string &tilemap)
{

	if (tilemap.size() <= 0) {
		Logger::logMessage(
			"ERROR loading tile map in loadTileMap function. Tile map vector is empty, please input a vector with values");
		return;
	}

	std::vector<std::string> lines = iow::splitStringBy(tilemap, "\n");
	// number of lines is the number of rows
	m_tileMapSize.x = lines.size();

	loadTileMap(lines);
}

void iow::TileMap::loadTileMap(std::vector<std::string> lines)
{
	std::vector<std::string> row = iow::splitStringBy(lines[0], " ");
	// number of columns is the number of space seperated things
	m_tileMapSize.y = row.size();

	for (size_t i = 0; i < lines.size(); ++i) {
		row = ::iow::splitStringBy(lines[i], " ");

		for (size_t j = 0; j < m_tileMapSize.y && j < row.size(); ++j) {
			if (!iow::isNumber(row[j])) {
				Logger::logMessage(
					"ERROR loading tile map at ROW:");
				Logger::logMessage(std::to_string(i).c_str());
				Logger::logMessage("and COLUMN:");
				Logger::logMessage(std::to_string(j).c_str());
				Logger::logMessage(
					"Please ensure that the tile map only contains numbers. Loading default val of 0 instead...");
				m_tiles.push_back(
					static_cast<iow::TileType>(0));
			} else {
				if (isValidTileType(std::stoi(row[j]))) {
					m_tiles.push_back(std::stoi(row[j]));
				} else {
					Logger::logMessage(
						"ERROR loading tile map at ROW:");
					Logger::logMessage(
						std::to_string(i).c_str());
					Logger::logMessage("and COLUMN:");
					Logger::logMessage(
						std::to_string(j).c_str());
					Logger::logMessage(
						"Please ensure that the tile map only contains valid enum values for tile types.. loading the defaul ttile type.");
					m_tiles.push_back(0);
				}
			}
		}

		if (row.size() > m_tileMapSize.y) {
			Logger::logMessage(
				"ERROR loading tile map. Ensure dimensions are the same for every row and column of the tilemap.  ROW:");
			Logger::logMessage(std::to_string(i).c_str());
			Logger::logMessage(
				"Is bigger than the initial row length of: ");
			Logger::logMessage(
				std::to_string(m_tileMapSize.y).c_str());
		}

		for (size_t j = 0; j < m_tileMapSize.y - row.size(); ++j) {
			Logger::logMessage(
				std::to_string(m_tileMapSize.y).c_str());
			Logger::logMessage(
				std::to_string(m_tileMapSize.y).c_str());
			Logger::logMessage("ERROR loading tile map at ROW:");
			Logger::logMessage(std::to_string(i).c_str());
			Logger::logMessage("and COLUMN:");
			Logger::logMessage(std::to_string(j).c_str());
			Logger::logMessage(
				"Please ensure the tile map has equal dimensions... loading the default 0 texture for these indices instead...");
			m_tiles.push_back(static_cast<iow::TileType>(0));
		}
	}
}

std::pair<iow::Position, iow::TileType> iow::TileMap::getTile(size_t i)
{
	auto tileIndexPosition = getTileCoord(i);
	return std::make_pair(
		sf::Vector2f(
			static_cast<float>(tileIndexPosition.x) * m_tileSize.x,
			static_cast<float>(tileIndexPosition.y) * m_tileSize.y),
		m_tiles[i]);
}

sf::Vector2i iow::TileMap::getTileCoord(size_t i)
{
	/* sf::Vector2i tileIndexPosition = sf::Vector2i( */
	/* 	m_tileMapSize.x - 1 - i / m_tileMapSize.y, i %
	 * m_tileMapSize.y); */
	return sf::Vector2i(i % m_tileMapSize.y,
			    m_tileMapSize.x - 1 - i / m_tileMapSize.y);
}

size_t iow::TileMap::getTileMapSize()
{
	return m_tiles.size();
}

void iow::TileMap::setTileConfig(size_t val, std::optional<TileConfig> conf)
{
	if (m_tileConfigs.size() >= val) {
		m_tileConfigs.resize(1 + val * 2);
	}

	conf->sprite.setTextureRect(
		sf::IntRect(0, 0, m_tileSize.x, m_tileSize.y));
	m_tileConfigs[val] = std::move(conf);
}

const iow::TileConfig iow::TileMap::getTileConfig(iow::TileType val)
{
	if (!m_tileConfigs[val].has_value()) {
		Logger::logMessage(
			"ERROR with getTileConfig. Ensure that the TileType you loaded has the required val loaded in already. You're attempting to load: ");
		Logger::logMessage(std::to_string(val).c_str());
		Logger::logMessage(
			"which does not exist. Loading tile config at 0, evreything may be undefine behaviour");
		return *m_tileConfigs[0];
	}
	return *m_tileConfigs[val];
}

void iow::TileMap::printTileMap()
{
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		// TODO implement this funciton
	}
}

bool iow::TileMap::isValidTileType(TileType n)
{

	if (n >= m_tileConfigs.size()) {
		return false;
	}

	if (!m_tileConfigs[n].has_value()) {
		return false;
	}

	return true;
}
