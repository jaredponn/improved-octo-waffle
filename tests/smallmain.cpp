#include "../src/graph.h"
#include "../src/pathfinding.h"
#include <iostream>

int main(void)
{

	constexpr size_t MAX_NEIGHBORS = 2;
	iow::Graph<char, MAX_NEIGHBORS> testGraph{};

	testGraph.m_graph.push_back(std::make_pair(
		'A',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(1, 5), iow::makeGraphEdge(2, 6)})));
	testGraph.m_graph.push_back(std::make_pair(
		'B',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(0, 5), iow::makeGraphEdge(3, 3)})));
	testGraph.m_graph.push_back(std::make_pair(
		'C',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(0, 6), iow::makeGraphEdge(3, 1)})));
	testGraph.m_graph.push_back(std::make_pair(
		'D',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(1, 3), iow::makeGraphEdge(2, 1)})));

	auto tmp = iow::Pathfinding::dijkstrasPath(testGraph, 0, 3);


	for (auto i : tmp) {
		std::cout << testGraph.dereferenceDataGraphCoord(i)
			  << std::endl;
	}


	return 0;
}
