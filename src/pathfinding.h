#pragma once

#include "graph.h"
#include <iostream>
#include <queue>
#include <vector>

namespace iow
{

namespace Pathfinding
{

using Distance = int;
const int MAX_DISTANCE = std::numeric_limits<int>::max();

// WARNING: will spin infinietly ify there is no optimal path
template <class T, size_t N>
static inline Distance dijkstras(iow::Graph<T, N> const &graph,
				 GraphCoord const start,
				 GraphCoord const destination)
{
	// distances of the graph
	std::vector<Distance> distances(graph.m_graph.size(), MAX_DISTANCE);

	std::vector<bool> visited(graph.m_graph.size(), false);

	std::queue<GraphCoord> toVisit;
	toVisit.push(start);

	visited[start] = true;
	distances[start] = 0;

	while (!toVisit.empty()) {
		// pop
		GraphCoord const focus = toVisit.front();
		toVisit.pop();

		visited[focus] = true;

		GraphNeighbors<N> const &neighbors = graph.getNeighbors(focus);

		// calculating the distances
		for (GraphEdge const &edge : neighbors) {
			GraphCoord const edgeCoord = std::get<0>(edge);
			GraphCoord const edgeCost = std::get<1>(edge);

			if (!iow::Graph<T, N>::isValidGraphEdge(edge)
			    || visited[edgeCoord])
				continue;

			Distance const newDistance =
				distances[focus] + edgeCost;

			if (newDistance < distances[edgeCoord]) {
				distances[edgeCoord] = newDistance;
			}

			toVisit.push(edgeCoord);
		}
	}

	return distances[destination];
}

template <class T, size_t N>
static inline std::vector<iow::GraphCoord>
aStar(iow::Graph<T, N> const &graph, std::queue<GraphCoord> &visited,
      GraphCoord focus, GraphCoord const start, GraphCoord const destination)
{
}

} // namespace Pathfinding
} // namespace iow
