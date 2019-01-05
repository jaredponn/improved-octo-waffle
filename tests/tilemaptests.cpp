#include "../extern/catch.hpp"
#include "../src/tilemap.h"

TEST_CASE("TileMap internal getters and setters of coordinates")
{

	// to
	iow::TileCoordi dimensions = iow::TileCoordi{5, 10};

	auto a = iow::TileMap::getTileCoord(1, dimensions);
	REQUIRE(iow::TileMap::getTileIndex(a, dimensions) == 1);

	a = iow::TileMap::getTileCoord(4, dimensions);
	REQUIRE(iow::TileMap::getTileIndex(a, dimensions) == 4);

	// from
	auto b = iow::TileMap::getTileIndex(iow::TileCoordi{2, 3}, dimensions);
	REQUIRE(iow::TileMap::getTileCoord(b, dimensions)
		== iow::TileCoordi{2, 3});

	b = iow::TileMap::getTileIndex(iow::TileCoordi{8, 2}, dimensions);
	REQUIRE(iow::TileMap::getTileCoord(b, dimensions)
		== iow::TileCoordi{8, 2});
}
