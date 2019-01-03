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


namespace PathFinding
{

// -----------------------------------------
//    Types
// -----------------------------------------

using GraphNeighbor = size_t;
using GraphCoord = size_t;
using GraphCost = int;

using GraphEdge = std::pair<GraphNeighbor, GraphCost>;

template <size_t N>
using GraphNeighbors = std::array<GraphEdge, N>;

template <typename T, size_t N>
using GraphVertex = std::pair<T, GraphNeighbors<N>>;


template <typename Data, typename T, size_t N>
class Graph
{
    public: // state
	std::vector<GraphVertex<T, N>> m_graph;
	GraphCoord m_focus;

    public: // working with the graph
	// gets the current focus of the graph
	virtual GraphCoord getFocus();
	// gets the edge
	virtual GraphEdge getEdge(GraphNeighbor const);


	virtual void setFocus(GraphCoord const);

    public: // dereferences and references
	virtual GraphVertex<T, N>
	dereferenceGraphCoord(GraphCoord const &coord);
	virtual GraphCoord referenceGraphCoord(GraphVertex<T, N> const &);

    public: // utitliy functions
	static inline bool isValidGraphEdge(GraphEdge const n)
	{
		return std::numeric_limits<int>::max() != std::get<0>(n);
	}

    public: // loading and creating the graph
	// converts the tilemap into the graph form
	virtual void loadGraph(Data const &data);
	virtual GraphNeighbors<N> createNeighbors(GraphCoord const,
						  Data const &tilemap) const;
};


template <typename Data, typename T, size_t N>
class PathindingGraph : public Graph<Data, T, N>
{
    public: // state
	GraphCoord m_start;
	GraphCoord m_destination;
	std::queue<GraphCoord> m_queue;

    public: // pathfindin
};


} // namespace PathFinding

} // namespace iow
