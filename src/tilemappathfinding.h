#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

#include "directions.h"
#include "graph.h"
#include "tilemap.h"
/* crikey this isn't C, refactor and make this a static class for cryin out loud
 */

// https://www.gamedev.net/articles/programming/artificial-intelligence/a-pathfinding-for-beginners-r2003/
namespace iow
{


// -----------------------------------------
//    constants
// -----------------------------------------


class TileMapPathfinding
{
    public:
	static constexpr size_t MAX_TILE_MAP_EDGES = 8;
	static constexpr GraphCost UP_DOWN_LEFT_RIGHT_COST = 10;
	static constexpr GraphCost DIAGONAL_COST = 14;

    public:
	// converts the tilemap into a graph
	iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>
	tileMapToGraph(iow ::TileMap const &tilemap);

	// create tilemap neighbors
	iow::GraphNeighbors<MAX_TILE_MAP_EDGES>
	createGraphNeighborFromTileMap(iow::TileCoordi const i,
				       iow::TileMap const &tilemap);

	// create the graph edge from the tilemap
	// TODO refactor the createGrahNeighborFromTileMap to use this
	// TODO not implemented
	iow::GraphEdge createGraphEdgeFromTileMap(iow::TileCoordi const i,
						  iow::Directions const d,
						  iow::TileMap const &tilemap);
};


// -----------------------------------------
//    definitions
// -----------------------------------------

iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>
iow::TileMapPathfinding::tileMapToGraph(iow ::TileMap const &tilemap)
{
	Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES> graph;

	size_t const tilemaplen = tilemap.getTileMapSize();

	for (auto i = 0; i < tilemaplen; ++i) {
		iow::TileCoordi const tmp = tilemap.getTileCoord(i);

		graph.m_graph.push_back(std::make_pair(
			tmp, createGraphNeighborFromTileMap(tmp, tilemap)));
	}
}

iow::GraphNeighbors<MAX_TILE_MAP_EDGES>
iow::TileMapPathfinding::createGraphNeighborFromTileMap(
	iow::TileCoordi const i, iow::TileMap const &tilemap)
{
	GraphEdge up;
	GraphEdge down;
	GraphEdge left;
	GraphEdge right;
	GraphEdge upRight;
	GraphEdge downRight;
	GraphEdge upLeft;
	GraphEdge downLeft;

	iow::TileCoordi const tileMapDimensions =
		tilemap.getTileMapDimensions();

	/* if the edges are out of bounds, just set it to out of bounds */
	// up
	if (i.row - 1 < 0) {
		up = iow::INVALID_GRAPH_EDGE;
		upRight = iow::INVALID_GRAPH_EDGE;
		upLeft = iow::INVALID_GRAPH_EDGE;
	}
	// down
	if (i.row + 1 >= tileMapDimensions.row) {
		down = iow::INVALID_GRAPH_EDGE;
		downRight = iow::INVALID_GRAPH_EDGE;
		downLeft = iow::INVALID_GRAPH_EDGE;
	}
	// left
	if (i.col - 1 < 0) {
		left = iow::INVALID_GRAPH_EDGE;
		upLeft = iow::INVALID_GRAPH_EDGE;
		downLeft = iow::INVALID_GRAPH_EDGE;
	}
	// right
	if (i.col + 1 >= tileMapDimensions.col) {
		right = iow::INVALID_GRAPH_EDGE;
		upRight = iow::INVALID_GRAPH_EDGE;
		downRight = iow::INVALID_GRAPH_EDGE;
	}


	/* setting up the graph if the coordinates are valid */
	// up
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    up)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row - 1, i.col};
		up = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					UP_DOWN_LEFT_RIGHT_COST);
	}

	// down
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    down)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row + 1, i.col};
		down = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					  UP_DOWN_LEFT_RIGHT_COST);
	}

	// left
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    left)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row, i.col - 1};
		left = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					  UP_DOWN_LEFT_RIGHT_COST);
	}

	// right
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    right)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row, i.col + 1};
		right = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					   UP_DOWN_LEFT_RIGHT_COST);
	}

	// upRight
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    upRight)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row - 1, i.col + 1};
		upRight = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					     DIAGONAL_COST);
	}

	// downRight
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    downRight)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row + 1, i.col + 1};
		downRight = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					       DIAGONAL_COST);
	}

	// upLeft
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    upLeft)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row - 1, i.col - 1};
		upLeft = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					    DIAGONAL_COST);
	}

	// downLeft
	if (iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>::isValidGraphEdge(
		    downLeft)) {
		iow::TileCoordi const nTileCoord =
			(TileCoord){i.row + 1, i.col - 1};
		downLeft = iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					      DIAGONAL_COST);
	}


	return {up, down, left, right, upRight, downRight, upLeft, downLeft};
}


} // namespace iow
