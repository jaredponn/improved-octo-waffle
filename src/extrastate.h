#pragma once
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "tilemappathfinding.h"


namespace iow
{
class ExtraState
{
    public:
	ExtraState();

	// state
	size_t m_player_entity;
	iow::Camera m_camera;

	iow::TileMapPathfinding::Graph m_tile_map_graph;
};

} // namespace iow
