#pragma once

#include "tilemap.h"
#include "logger.h"

void iow::TileMap::assertSize()
{
	if (tileSize.x * tileSize.y != tiles.size())
		Logger::logMessage(
			"ERROR with tile map config -- the width and the height of the tilemap must be the same as the .size() aof the tiles vector.");
}
