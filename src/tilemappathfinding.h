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
//    declarations
// -----------------------------------------


class TileMapPathfinding
{

    public:
	static constexpr size_t MAX_TILE_MAP_EDGES = 8;
	static constexpr GraphCost UP_DOWN_LEFT_RIGHT_COST = 10;
	static constexpr GraphCost DIAGONAL_COST = 14;

    public:
	using Graph = iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>;

    public:
	// converts the tilemap into a graph
	static iow::Graph<iow::TileCoordi, MAX_TILE_MAP_EDGES>
	tileMapToGraph(iow ::TileMap const &tilemap);

	// create tilemap neighbors
	static iow::GraphNeighbors<MAX_TILE_MAP_EDGES>
	createGraphNeighborFromTileMap(iow::TileCoordi const i,
				       iow::TileMap const &tilemap);

	// create the graph edge from the tilemap
	// TODO refactor the createGrahNeighborFromTileMap to use this
	// TODO not implemented
	static iow::GraphEdge
	determineGraphEdgeFromTileMapAndDirection(iow::TileCoordi const i,
						  iow::Directions const d,
						  iow::TileMap const &tilemap);

	static bool
	isGraphCoordWall(iow::TileMapPathfinding::Graph const &graph,
			 iow::GraphCoord const n);
};


// -----------------------------------------
//    definitions
// -----------------------------------------

inline iow::Graph<iow::TileCoordi, TileMapPathfinding::MAX_TILE_MAP_EDGES>
iow::TileMapPathfinding::tileMapToGraph(iow ::TileMap const &tilemap)
{
	iow::Graph<iow::TileCoordi, TileMapPathfinding::MAX_TILE_MAP_EDGES>
		graph;

	size_t const tilemaplen = tilemap.getTileMapSize();

	for (size_t i = 0; i < tilemaplen; ++i) {
		iow::TileCoordi const tmp = tilemap.getTileCoord(i);

		graph.m_graph.push_back(std::make_pair(
			tmp, createGraphNeighborFromTileMap(tmp, tilemap)));
	}

	return graph;
}

inline iow::GraphNeighbors<TileMapPathfinding::MAX_TILE_MAP_EDGES>
iow::TileMapPathfinding::createGraphNeighborFromTileMap(
	iow::TileCoordi const i, iow::TileMap const &tilemap)
{
	GraphEdge up = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::UP, tilemap);
	GraphEdge down = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::DOWN, tilemap);
	GraphEdge left = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::LEFT, tilemap);
	GraphEdge right = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::RIGHT, tilemap);
	GraphEdge upRight = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::UP_RIGHT, tilemap);
	GraphEdge downRight = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::DOWN_RIGHT, tilemap);
	GraphEdge upLeft = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::UP_LEFT, tilemap);
	GraphEdge downLeft = determineGraphEdgeFromTileMapAndDirection(
		i, iow::Directions::DOWN_LEFT, tilemap);

	return {up, down, left, right, upRight, downRight, upLeft, downLeft};
}

inline iow::GraphEdge
iow::TileMapPathfinding::determineGraphEdgeFromTileMapAndDirection(
	iow::TileCoordi const i, iow::Directions const d,
	iow::TileMap const &tilemap)
{

	iow::TileCoordi const tileMapDimensions =
		tilemap.getTileMapDimensions();

	sf::Vector2i const unitDirectionVec =
		iow::convertDirectionToUnitVector(d);

	iow::TileCoordi const nTileCoord = i + unitDirectionVec;

	/* if the edges are out of bounds, just set it to out of bounds */
	// for the rows
	if (nTileCoord.row < 0 || nTileCoord.row >= tileMapDimensions.row) {
		return iow::INVALID_GRAPH_EDGE;
	}
	// for the columns
	if (nTileCoord.col < 0 || nTileCoord.col >= tileMapDimensions.col) {
		return iow::INVALID_GRAPH_EDGE;
	}

	const auto &nTileConf =
		tilemap.getTileConfig(tilemap.getTileType(nTileCoord));
	const auto &fTileConf = tilemap.getTileConfig(tilemap.getTileType(i));

	// if either is a wall, give it the max cost
	if (nTileConf.collision || fTileConf.collision) {
		return iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					  iow ::MAX_GRAPH_COST);
	}

	if (iow::isVerticalOrHorizontalDirection(d)) {
		return iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					  UP_DOWN_LEFT_RIGHT_COST);
	} else {
		return iow::makeGraphEdge(tilemap.getTileIndex(nTileCoord),
					  DIAGONAL_COST);
	}
}


inline bool iow::TileMapPathfinding::isGraphCoordWall(
	iow::TileMapPathfinding::Graph const &graph, iow::GraphCoord const n)
{
	GraphNeighbors<iow::TileMapPathfinding::MAX_TILE_MAP_EDGES> const
		&neighbors = graph.dereferenceVertexGraphCoord(n).second;

	for (auto const &i : neighbors) {
		if (i.second != iow::MAX_GRAPH_COST)
			return false;
	}
	return true;
}

} // namespace iow
