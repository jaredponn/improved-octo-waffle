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

template <size_t N>
using GraphNeighbors = std::array<GraphEdge, N>;

template <typename T, size_t N>
using GraphVertex = std::pair<T, GraphNeighbors<N>>;

const int INVALID_GRAPH_COORD = std::numeric_limits<int>::max();

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
	GraphVertex<T, N> dereferenceGraphCoord(GraphCoord const &coord) const;
	GraphCoord referenceGraphCoord(GraphVertex<T, N> const &) const;

    public: // utitliy functions
	bool isValidGraphEdge(GraphEdge const n) const;
};

template <class T, size_t N>
inline bool iow::Graph<T, N>::isValidGraphEdge(GraphEdge const n) const
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
inline GraphVertex<T, N>
iow::Graph<T, N>::dereferenceGraphCoord(GraphCoord const &n) const
{
	return m_graph[n];
}

template <class T, size_t N>
inline GraphCoord
iow::Graph<T, N>::referenceGraphCoord(GraphVertex<T, N> const &vertex) const
{
	return (GraphCoord)(&vertex - m_graph[0]);
}


template <class T, size_t N>
iow::Graph<T, N>::Graph()
{
}

template <class T, size_t N>
iow::Graph<T, N>::~Graph()
{
}

} // namespace iow
