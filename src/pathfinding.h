#pragma once

#include "graph.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

namespace iow
{

namespace Pathfinding
{

using Distance = int;
const int MAX_DISTANCE = std::numeric_limits<int>::max();

// -----------------------------------------
//    declarations
// -----------------------------------------

//  finds the shortest distance to a point in the graph
// NOTE: returns MAX_DISTANCE if there is no such path that exists
template <class T, size_t N>
static inline Distance dijkstras(iow::Graph<T, N> const &graph,
				 GraphCoord const start,
				 GraphCoord const destination);

// returns the vector of all distances from start to any node.
template <class T, size_t N>
static inline std::vector<Distance>
dijkstrasDistances(iow::Graph<T, N> const &graph, GraphCoord const start,
		   GraphCoord const destination);

// returns the GraphCoords of the shortest path to the point from start to
// destination
template <class T, size_t N>
static inline std::vector<GraphCoord>
dijkstrasPath(iow::Graph<T, N> const &graph, GraphCoord const start,
	      GraphCoord const destination);

// -----------------------------------------
//    implementation
// -----------------------------------------

template <class T, size_t N>
static inline std::vector<Distance>
dijkstrasDistances(iow::Graph<T, N> const &graph, GraphCoord const start,
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

			/* optimization to only visit the future nodes that are
			 * smaller than the current destination node */
			if (distances[edgeCoord] < distances[destination]) {

				toVisit.push(edgeCoord);
			}
		}
	}

	return distances;
}


// will return  MAX_DISTANCE if there is no such path that exists
template <class T, size_t N>
static inline Distance dijkstras(iow::Graph<T, N> const &graph,
				 GraphCoord const start,
				 GraphCoord const destination)
{
	return dijkstrasDistances(graph, start, destination)[destination];
}

template <class T, size_t N>
static inline std::vector<GraphCoord>
dijkstrasPath(iow::Graph<T, N> const &graph, GraphCoord const start,
	      GraphCoord const destination)
{
	// distances of the graph
	std::vector<Distance> distances(graph.m_graph.size(), MAX_DISTANCE);

	// back tracking to find the path (keeps track of the parent node)
	std::vector<GraphCoord> backtracking(graph.m_graph.size(),
					     iow::INVALID_GRAPH_COORD);

	std::vector<bool> visited(graph.m_graph.size(), false);

	std::queue<GraphCoord> toVisit;
	toVisit.push(start);

	visited[start] = true;
	distances[start] = 0;
	backtracking[start] = start;

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
				backtracking[edgeCoord] = focus;
				distances[edgeCoord] = newDistance;
			}

			/* optimization to only visit the future nodes that are
			 * smaller than the current destination node */
			if (distances[edgeCoord] < distances[destination]) {

				toVisit.push(edgeCoord);
			}
		}
	}

	// returning the path:
	std::vector<GraphCoord> path;

	// if no path exists, return no path;
	if (backtracking[destination] == iow::INVALID_GRAPH_COORD)
		return path;

	GraphCoord focus = destination;

	while (focus != start) {
		path.push_back(focus);
		focus = backtracking[focus];
	}
	path.push_back(start);
	std::reverse(path.begin(), path.end());

	return path;
}


} // namespace Pathfinding
} // namespace iow
