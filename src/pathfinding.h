#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

#include "directions.h"
#include "tilemap.h"
// https://www.gamedev.net/articles/programming/artificial-intelligence/a-pathfinding-for-beginners-r2003/

namespace iow
{


namespace PathFinding
{

// -----------------------------------------
//    Types
// -----------------------------------------

using GraphNeighbor = sf::Vector2i;
using GraphCost = int;

using GraphEdge = std::pair<GraphNeighbor, GraphCost>;
using GraphCoord = sf::Vector2i;

// clang-format off
using GraphNeighbors = std::tuple<GraphEdge // iow::Direcion::UP
                                , GraphEdge // iow::Direcion::DOWN
                                , GraphEdge // iow::Direcion::LEFT
                                , GraphEdge // iow::Direcion::RIGHT
                                , GraphEdge // iow::Direcion::UP_RIGHT
                                , GraphEdge // iow::Direcion::DOWN_RIGHT
                                , GraphEdge // iow::Direcion::UP_LEFT
                                , GraphEdge // iow::Direcion::DOWN_LEFT
                                >;
// clang-format on
using GraphVertex = std::pair<GraphCoord, GraphNeighbors>;

// -----------------------------------------
//    Constants
// -----------------------------------------
constexpr int MOVEMENT_WEIGHT = 10;
constexpr int DIAGONAL_MOVEMENT_WEIGHT = 14;
const sf::Vector2i INVALID_GRAPH_EDGE = sf::Vector2i{
	std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
const GraphCost MAX_GRAPH_COST = std::numeric_limits<int>::max();

class TileMapGraph
{
    private:
	std::vector<GraphVertex> m_graph;
	sf::Vector2u m_graph_dimensions;

	GraphCoord m_focus;
	GraphCoord m_start;
	GraphCoord m_destination;

    public: // working with the graph
	// gets the current focus of the graph
	GraphCoord getFocus();
	// gets the neighobr in a given direction
	GraphEdge getNeighbor(iow::Directions &direction);

	GraphVertex dereferenceGraphCoord(GraphCoord const &coord);

    public: // loading functions
	// converts the tilemap into the graph form
	void loadGraph(TileMap const &tilemap);

    public: // utitliy functions
	static inline bool isValidGraphEdge(GraphEdge const n)
	{
		return std::numeric_limits<int>::max() != std::get<0>(n).x
		       || std::numeric_limits<int>::max() != std::get<0>(n).y;
	}

    private:
	GraphNeighbors createNeighbors(GraphCoord const,
				       TileMap const &tilemap) const;
	GraphEdge
	createEdgeToCoordFromTileMap(GraphCoord const &coord,
				     iow::Direction const &directionTo,
				     TileMap const &tilemap) const;
};


} // namespace PathFinding

} // namespace iow
