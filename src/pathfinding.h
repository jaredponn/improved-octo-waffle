#pragma once

#include "graph.h"
#include "logger.h"

#include <algorithm>
#include <functional>
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
inline Distance dijkstras(iow::Graph<T, N> const &graph, GraphCoord const start,
			  GraphCoord const destination);

// returns the vector of all distances from start to any node.
template <class T, size_t N>
inline std::vector<Distance> dijkstrasDistances(iow::Graph<T, N> const &graph,
						GraphCoord const start,
						GraphCoord const destination);


template <class T, size_t N, class U>
class ShortestPath
{
    public:
	// returns the GraphCoords of the shortest path to the point from start
	// to destination. T is the data type of the graph, U is the return type
	// of the function
	static inline std::vector<U>
	dijkstrasPath(iow::Graph<T, N> const &graph, GraphCoord const start,
		      GraphCoord const destination,
		      std::function<U(T const)> = [](T const a) { return a; });

	// returns the GraphCoords of the shortest path to the point from start
	// to destination. T is the data type of the graph, U is the return type
	// of the function
	static inline std::vector<U> dijkstrasReversedPath(
		iow::Graph<T, N> const &graph, GraphCoord const start,
		GraphCoord const destination,
		std::function<U(T const)> = [](T const a) { return a; });
};

// -----------------------------------------
//    implementation
// -----------------------------------------

template <class T, size_t N>
inline std::vector<Distance> dijkstrasDistances(iow::Graph<T, N> const &graph,
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
inline Distance dijkstras(iow::Graph<T, N> const &graph, GraphCoord const start,
			  GraphCoord const destination)
{
	return dijkstrasDistances(graph, start, destination)[destination];
}

// calculates the new distances -- if either are MAX_DISTANCE it just returns
// MAX_DISTANCE instead of doing overflow behaviour
inline Distance calculateNewDistance(Distance const a, Distance const b)
{
	if (a == MAX_DISTANCE)
		return MAX_DISTANCE;

	if (b == MAX_DISTANCE)
		return MAX_DISTANCE;

	return a + b;
}


template <class T, size_t N, class U>
inline std::vector<U> ShortestPath<T, N, U>::dijkstrasPath(
	iow::Graph<T, N> const &graph, GraphCoord const start,
	GraphCoord const destination, std::function<U(T const)> func)
{
	std::vector<U> path = ShortestPath<T, N, U>::dijkstrasReversedPath(
		graph, start, destination, func);
	std::reverse(path.begin(), path.end());
	return path;
}


template <class T, size_t N, class U>
inline std::vector<U> ShortestPath<T, N, U>::dijkstrasReversedPath(
	iow::Graph<T, N> const &graph, GraphCoord const start,
	GraphCoord const destination, std::function<U(T const)> func)
{

	if (start >= graph.m_graph.size()
	    || destination >= graph.m_graph.size()) {
		Logger::logMessage(
			"Error in dijkstras -- start / destination are out of bounds");
		return std::vector<U>();
	}

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

			Distance const newDistance = calculateNewDistance(
				distances[focus], edgeCost);

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
	std::vector<U> path;

	// if no path exists, return no path;
	if (backtracking[destination] == iow::INVALID_GRAPH_COORD)
		return path;

	GraphCoord focus = destination;

	while (focus != start) {
		path.push_back((func)(graph.dereferenceDataGraphCoord(focus)));
		focus = backtracking[focus];
	}
	path.push_back((func)(graph.dereferenceDataGraphCoord(focus)));

	return path;
}

} // namespace Pathfinding
} // namespace iow
