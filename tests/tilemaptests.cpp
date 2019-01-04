#include "../extern/catch.hpp"
#include "../src/graph.h"

TEST_CASE("Graphs referencing and dereferencing tests")
{

	iow::Graph<int, 2> testGraph{};

	REQUIRE(1 == 1);
}
