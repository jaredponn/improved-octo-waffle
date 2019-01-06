#include "../extern/catch.hpp"
#include "../src/graph.h"
#include "../src/pathfinding.h"


TEST_CASE("Graphs referencing and dereferencing tests")
{
	constexpr size_t MAX_NEIGHBORS = 2;
	iow::Graph<int, MAX_NEIGHBORS> testGraph{};

	testGraph.m_graph.push_back(std::make_pair(
		0, iow::GraphNeighbors<MAX_NEIGHBORS>(
			   {iow::makeGraphEdge(1), iow::makeGraphEdge(2)})));
	testGraph.m_graph.push_back(std::make_pair(
		1, iow::GraphNeighbors<MAX_NEIGHBORS>(
			   {iow::makeGraphEdge(2), iow::makeGraphEdge(3)})));
	testGraph.m_graph.push_back(std::make_pair(
		2, iow::GraphNeighbors<MAX_NEIGHBORS>(
			   {iow::makeGraphEdge(3),
			    iow::makeGraphEdge(iow::INVALID_GRAPH_COORD)})));
	testGraph.m_graph.push_back(std::make_pair(
		3, iow::GraphNeighbors<MAX_NEIGHBORS>(
			   {iow::makeGraphEdge(iow::INVALID_GRAPH_COORD),
			    iow::makeGraphEdge(iow::INVALID_GRAPH_COORD)})));

	REQUIRE(testGraph.dereferenceDataGraphCoord(0) == 0);
	REQUIRE(testGraph.dereferenceDataGraphCoord(1) == 1);
	REQUIRE(testGraph.dereferenceDataGraphCoord(2) == 2);
	REQUIRE(testGraph.dereferenceDataGraphCoord(3) == 3);

	REQUIRE(testGraph.referenceGraphCoord(
			testGraph.dereferenceVertexGraphCoord(0))
		== 0);
	REQUIRE(testGraph.referenceGraphCoord(
			testGraph.dereferenceVertexGraphCoord(1))
		== 1);
	REQUIRE(testGraph.referenceGraphCoord(
			testGraph.dereferenceVertexGraphCoord(2))
		== 2);
	REQUIRE(testGraph.referenceGraphCoord(
			testGraph.dereferenceVertexGraphCoord(3))
		== 3);
}


TEST_CASE("Dijstraks test case 0")
{
	constexpr size_t MAX_NEIGHBORS = 1;
	iow::Graph<char, MAX_NEIGHBORS> testGraph{};
	testGraph.m_graph.push_back(
		std::make_pair('A', iow::GraphNeighbors<MAX_NEIGHBORS>(
					    {iow::makeGraphEdge(1, 3)})));
	testGraph.m_graph.push_back(
		std::make_pair('B', iow::GraphNeighbors<MAX_NEIGHBORS>(
					    {iow::makeGraphEdge(0, 3)})));


	REQUIRE(iow::Pathfinding::dijkstras(testGraph, 0, 1) == 3);
}

TEST_CASE("Dijstraks test case 0 -- backtracking")
{
	constexpr size_t MAX_NEIGHBORS = 1;
	iow::Graph<char, MAX_NEIGHBORS> testGraph{};
	testGraph.m_graph.push_back(
		std::make_pair('A', iow::GraphNeighbors<MAX_NEIGHBORS>(
					    {iow::makeGraphEdge(1, 3)})));
	testGraph.m_graph.push_back(
		std::make_pair('B', iow::GraphNeighbors<MAX_NEIGHBORS>(
					    {iow::makeGraphEdge(0, 3)})));

	auto path = iow::Pathfinding::dijkstrasPath(testGraph, 0, 1);

	REQUIRE(testGraph.dereferenceDataGraphCoord(path[0]) == 'A');
	REQUIRE(testGraph.dereferenceDataGraphCoord(path[1]) == 'B');
}

TEST_CASE("Dijstraks test case 1")
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

	REQUIRE(iow::Pathfinding::dijkstras(testGraph, 0, 3) == 7);
}

TEST_CASE("Dijstraks test case 1 -- backtracking")
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

	REQUIRE(testGraph.dereferenceDataGraphCoord(tmp[0]) == 'A');
	REQUIRE(testGraph.dereferenceDataGraphCoord(tmp[1]) == 'C');
	REQUIRE(testGraph.dereferenceDataGraphCoord(tmp[2]) == 'D');
}


TEST_CASE("Dijstraks test case 2")
{
	constexpr size_t MAX_NEIGHBORS = 4;
	iow::Graph<char, MAX_NEIGHBORS> testGraph{};

	testGraph.m_graph.push_back(std::make_pair(
		'A',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(1, 3), iow::makeGraphEdge(2, 1),
			 iow::INVALID_GRAPH_EDGE, iow::INVALID_GRAPH_EDGE})));
	testGraph.m_graph.push_back(std::make_pair(
		'B',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(0, 3), iow::makeGraphEdge(2, 7),
			 iow::makeGraphEdge(3, 5), iow::makeGraphEdge(4, 1)})));

	testGraph.m_graph.push_back(std::make_pair(
		'C',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(0, 1), iow::makeGraphEdge(1, 7),
			 iow::makeGraphEdge(3, 2), iow::INVALID_GRAPH_EDGE})));

	testGraph.m_graph.push_back(std::make_pair(
		'D',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(2, 2), iow::makeGraphEdge(1, 5),
			 iow::makeGraphEdge(4, 7), iow::INVALID_GRAPH_EDGE})));

	testGraph.m_graph.push_back(std::make_pair(
		'E',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(1, 1), iow::makeGraphEdge(3, 7),
			 iow::INVALID_GRAPH_EDGE, iow::INVALID_GRAPH_EDGE})));

	REQUIRE(iow::Pathfinding::dijkstras(testGraph, 2, 4) == 5);
}

TEST_CASE("Dijstraks test case 3 -- no best path exists")
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
			{iow::makeGraphEdge(0, 5), iow::INVALID_GRAPH_EDGE})));
	testGraph.m_graph.push_back(std::make_pair(
		'C',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(0, 6), iow::INVALID_GRAPH_EDGE})));
	testGraph.m_graph.push_back(std::make_pair(
		'D',
		iow::GraphNeighbors<MAX_NEIGHBORS>(
			{iow::makeGraphEdge(1, 3), iow::makeGraphEdge(2, 1)})));

	REQUIRE(iow::Pathfinding::dijkstras(testGraph, 0, 3)
		== iow::Pathfinding::MAX_DISTANCE);

	REQUIRE(iow::Pathfinding::dijkstrasPath(testGraph, 0, 3).size() == 0);
}
