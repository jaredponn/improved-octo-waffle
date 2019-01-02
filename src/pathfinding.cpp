#include "pathfinding.h"
#include "logger.h"

namespace iow
{
namespace PathFinding
{

GraphCoord iow::PathFinding::TileMapGraph::getFocus()
{
	return m_focus;
}

GraphEdge
iow::PathFinding::TileMapGraph::getNeighbor(iow::Directions &direction)
{

	switch (direction) {
	case iow::Directions::UP:
		return std::get<0>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::DOWN:
		return std::get<1>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::LEFT:
		return std::get<2>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::RIGHT:
		return std::get<3>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::UP_RIGHT:
		return std::get<4>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::DOWN_RIGHT:
		return std::get<5>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::UP_LEFT:
		return std::get<6>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::DOWN_LEFT:
		return std::get<7>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;

	case iow::Directions::INVALID_DIRECTION:
		Logger::logMessage(
			"MAJOR ERROR in pathfinding: Invalid direction in function getNeighbor. Please ensure you only pass a valid function in");
		return std::get<0>(std::get<1>(dereferenceGraphCoord(m_focus)));
		break;
	}
}


void iow::PathFinding::TileMapGraph::loadGraph(TileMap const &tilemap)
{
	size_t const tileMapLength = tilemap.getTileMapSize();
	GraphVertex tmp;

	for (size_t i = 0; i < tileMapLength; ++i) {
		auto tmpcoord = tilemap.getTileCoord(i);
		tmp = std::make_pair(tmpcoord,
				     createNeighbors(tmpcoord, tilemap));
		m_graph.push_back(tmp);
	}
}

GraphVertex
iow::PathFinding::TileMapGraph::dereferenceGraphCoord(GraphCoord const &coord)
{
	return m_graph[iow::TileMap::getTileIndex(coord, m_graph_dimensions)];
}

GraphNeighbors
iow::PathFinding::TileMapGraph::createNeighbors(GraphCoord const coord,
						TileMap const &tilemap) const
{

	GraphEdge up = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge down = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge left = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge right = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge upRight = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge downRight = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge upLeft = std::make_pair(sf::Vector2i{0, 0}, 0);
	GraphEdge downLeft = std::make_pair(sf::Vector2i{0, 0}, 0);

	if (coord.y + 1 >= (int)m_graph_dimensions.y) {
		up = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		upRight = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		upLeft = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
	}

	if (coord.y - 1 <= 0) {
		down = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		downRight = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		downLeft = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
	}

	if (coord.x + 1 >= (int)m_graph_dimensions.x) {
		right = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		upRight = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		downRight = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
	}

	if (coord.x - 1 <= 0) {
		left = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		upLeft = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
		downLeft = std::make_pair(INVALID_GRAPH_EDGE, MAX_GRAPH_COST);
	}


	if (isValidGraphEdge(up)) {
		up = createEdgeToCoordFromTileMap(coord, iow::Directions::UP,
						  tilemap);
	}
	if (isValidGraphEdge(down)) {
		down = createEdgeToCoordFromTileMap(
			coord, iow::Directions::DOWN, tilemap);
	}
	if (isValidGraphEdge(left)) {
		left = createEdgeToCoordFromTileMap(
			coord, iow::Directions::LEFT, tilemap);
	}
	if (isValidGraphEdge(right)) {
		right = createEdgeToCoordFromTileMap(
			coord, iow::Directions::RIGHT, tilemap);
	}
	if (isValidGraphEdge(upRight)) {
		upRight = createEdgeToCoordFromTileMap(
			coord, iow::Directions::UP_RIGHT, tilemap);
	}
	if (isValidGraphEdge(downRight)) {
		downRight = createEdgeToCoordFromTileMap(
			coord, iow::Directions::DOWN, tilemap);
	}
	if (isValidGraphEdge(upLeft)) {
		upLeft = createEdgeToCoordFromTileMap(
			coord, iow::Directions::UP_LEFT, tilemap);
	}
	if (isValidGraphEdge(downLeft)) {
		downLeft = createEdgeToCoordFromTileMap(
			coord, iow::Directions::DOWN_LEFT, tilemap);
	}


	return std::make_tuple(up, down, left, right, upRight, downRight,
			       upLeft, downLeft);
}

GraphEdge iow::PathFinding::TileMapGraph::createEdgeToCoordFromTileMap(
	GraphCoord const &coord, iow::Direction const &directionTo,
	TileMap const &tilemap) const
{

	sf::Vector2i ncoord;
	GraphCost ncost;

	switch (directionTo) {
	case iow::Directions::UP:
		ncoord = sf::Vector2i{coord.x, coord.y + 1};
		ncost = MOVEMENT_WEIGHT;
		break;
	case iow::Directions::DOWN:
		ncoord = sf::Vector2i{coord.x, coord.y - 1};
		ncost = MOVEMENT_WEIGHT;
		break;

	case iow::Directions::LEFT:
		ncoord = sf::Vector2i{coord.x - 1, coord.y};
		ncost = MOVEMENT_WEIGHT;
		break;

	case iow::Directions::RIGHT:
		ncoord = sf::Vector2i{coord.x + 1, coord.y};
		ncost = MOVEMENT_WEIGHT;
		break;

	case iow::Directions::UP_RIGHT:
		ncoord = sf::Vector2i{coord.x + 1, coord.y + 1};
		ncost = DIAGONAL_MOVEMENT_WEIGHT;
		break;
	case iow::Directions::DOWN_RIGHT:
		ncoord = sf::Vector2i{coord.x + 1, coord.y - 1};
		ncost = DIAGONAL_MOVEMENT_WEIGHT;
		break;

	case iow::Directions::UP_LEFT:
		ncoord = sf::Vector2i{coord.x - 1, coord.y + 1};
		ncost = DIAGONAL_MOVEMENT_WEIGHT;
		break;
	case iow::Directions::DOWN_LEFT:
		ncoord = sf::Vector2i{coord.x - 1, coord.y - 1};
		ncost = DIAGONAL_MOVEMENT_WEIGHT;
		break;
	case iow::Directions::INVALID_DIRECTION:
		Logger::logMessage(
			"ERROR invalid direction in createEdgeToCoordFromTileMap.PATHFINDING is BROKEN NOW");
		ncoord = sf::Vector2i{coord.x, coord.y};
		ncost = MOVEMENT_WEIGHT;
		break;
	}

	auto const tile = tilemap.getTile(tilemap.getTileIndex(coord));

	if (tilemap.getTileConfig(std::get<1>(tile)).collision) {
		return std::make_pair(ncoord, MAX_GRAPH_COST);
	} else {
		return std::make_pair(ncoord, ncost);
	}
}

// TODO graph should be finished, just implement the trivial dijkstras algrotihm

} // namespace PathFinding

} // namespace iow
