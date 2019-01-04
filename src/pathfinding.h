#pragma once

#include "graph.h"

namespace iow
{

namespace Pathfinding
{

template <class T, size_t N>
static inline std::vector<iow::GraphCoord>
aStar(iow::Graph<T, N> const &graph, std::queue<GraphCoord> &visited,
      GraphCoord focus, GraphCoord const start, GraphCoord const destination)
{
}

} // namespace Pathfinding
} // namespace iow
