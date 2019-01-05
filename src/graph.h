#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// https://www.gamedev.net/articles/programming/artificial-intelligence/a-pathfinding-for-beginners-r2003/
namespace iow
{


// -----------------------------------------
//    Types
// -----------------------------------------

using GraphCoord = size_t;
using GraphCost = int;

using GraphEdge = std::pair<GraphCoord, GraphCost>;
static inline GraphEdge makeGraphEdge(size_t const coordTo, int const cost = 0);

template <size_t N>
using GraphNeighbors = std::array<GraphEdge, N>;

template <typename T, size_t N>
using GraphVertex = std::pair<T, GraphNeighbors<N>>;

const GraphCoord INVALID_GRAPH_COORD = SIZE_MAX;
const GraphCost MAX_GRAPH_COST = std::numeric_limits<int>::max();
const GraphEdge INVALID_GRAPH_EDGE =
	makeGraphEdge(INVALID_GRAPH_COORD, MAX_GRAPH_COST);

template <class T, size_t N>
class Graph
{
    public: // state
	std::vector<GraphVertex<T, N>> m_graph;

    public: // Constructor / deconstructor
	Graph();
	~Graph();

    public: // working with the graph
	// gets the edge
	GraphNeighbors<N> const &getNeighbors(GraphCoord const) const;


    public: // dereferences and references
	T dereferenceDataGraphCoord(GraphCoord const &coord) const;
	GraphVertex<T, N> const &
	dereferenceVertexGraphCoord(GraphCoord const &coord) const;
	GraphCoord referenceGraphCoord(GraphVertex<T, N> const &) const;

    public: // utitliy functions
	static bool isValidGraphEdge(GraphEdge const n);
};

template <class T, size_t N>
inline bool iow::Graph<T, N>::isValidGraphEdge(GraphEdge const n)
{
	return INVALID_GRAPH_COORD != std::get<0>(n);
}

template <class T, size_t N>
inline GraphNeighbors<N> const &
iow::Graph<T, N>::getNeighbors(GraphCoord const n) const
{
	return std::get<1>(m_graph[n]);
}

template <class T, size_t N>
inline GraphVertex<T, N> const &
iow::Graph<T, N>::dereferenceVertexGraphCoord(GraphCoord const &n) const
{
	return m_graph[n];
}

template <class T, size_t N>
inline GraphCoord
iow::Graph<T, N>::referenceGraphCoord(GraphVertex<T, N> const &vertex) const
{
	return (GraphCoord)(&vertex - &m_graph[0]);
}

template <class T, size_t N>
inline T
iow::Graph<T, N>::dereferenceDataGraphCoord(GraphCoord const &coord) const
{
	return std::get<0>(dereferenceVertexGraphCoord(coord));
}

template <class T, size_t N>
iow::Graph<T, N>::Graph()
{
}

template <class T, size_t N>
iow::Graph<T, N>::~Graph()
{
}

static inline GraphEdge makeGraphEdge(size_t const coordTo, int const cost)
{
	return std::make_pair(coordTo, cost);
}

} // namespace iow
