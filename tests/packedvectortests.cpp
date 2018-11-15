// 010-TestCase.cpp

#include "../extern/catch.hpp"
#include "../src/packedvector.h"
#include "../src/collision.cpp"
#include <SFML/Graphics.hpp>

TEST_CASE("testing collisions")
{

	sf::RectangleShape rect1(sf::Vector2f(20.f, 20.f));
	sf::RectangleShape rect2(sf::Vector2f(50.f, 20.f));
	rect1.setPosition(50.f, 50.f);
	rect2.setPosition(30.f, 40.f);
	rect2.setFillColor(sf::Color(100, 200, 250));

	auto tmp = iow::checkCollision(rect1, rect2);
	if (tmp) {
		REQUIRE(tmp->x == 0);
		REQUIRE(tmp->y == 10);
		// std::cout << tmp->x << std::endl;
		// std::cout << tmp->y << std::endl;
	}
}

TEST_CASE("Creating a packedvector")
{
	iow::PackedVector<int> testPkdVec(10);
	REQUIRE(testPkdVec.get_packed_indicies().size() == 0);
	REQUIRE(testPkdVec.get_packed_data().size() == 0);
	REQUIRE(testPkdVec.get_sparse_vector().size() == 10);
}

TEST_CASE("Adding stuff to the packed vector ")
{
	iow::PackedVector<int> testPkdVec(10);
	testPkdVec.add_element_at_sparse_vector(5, 69);

	REQUIRE(testPkdVec.get_packed_data()[0] == 69);
	REQUIRE(testPkdVec.get_packed_indicies()[0] == 5);
	REQUIRE(testPkdVec.get_sparse_vector()[5] == 0);

	testPkdVec.add_element_at_sparse_vector(9, 96);
	REQUIRE(testPkdVec.get_packed_data()[1] == 96);
	REQUIRE(testPkdVec.get_packed_indicies()[1] == 9);
	REQUIRE(testPkdVec.get_sparse_vector()[9] == 1);

	testPkdVec.add_element_at_sparse_vector(2, 126);
	REQUIRE(testPkdVec.get_packed_data()[1] == 96);
	REQUIRE(testPkdVec.get_packed_indicies()[1] == 9);
	REQUIRE(testPkdVec.get_sparse_vector()[9] == 1);
}

TEST_CASE("Testing the get_data_from_sparse_vector")
{
	iow::PackedVector<int> testPkdVec(10);
	testPkdVec.add_element_at_sparse_vector(5, 69);
	testPkdVec.add_element_at_sparse_vector(9, 96);
	testPkdVec.add_element_at_sparse_vector(2, 126);

	REQUIRE(testPkdVec.get_data_from_sparse_vector(5) == 69);
	REQUIRE(testPkdVec.get_data_from_sparse_vector(9) == 96);
	REQUIRE(testPkdVec.get_data_from_sparse_vector(2) == 126);
}

TEST_CASE("Deleting stuff in the packed vector")
{
	iow::PackedVector<int> testPkdVec(10);
	testPkdVec.add_element_at_sparse_vector(5, 69);
	testPkdVec.add_element_at_sparse_vector(9, 96);
	testPkdVec.add_element_at_sparse_vector(2, 126);

	testPkdVec.delete_element_at_sparse_vector(5);

	REQUIRE(testPkdVec.get_data_from_sparse_vector(9) == 96);
	REQUIRE(testPkdVec.get_packed_indicies()[1] == 9);

	REQUIRE(testPkdVec.get_data_from_sparse_vector(2) == 126);
	REQUIRE(testPkdVec.get_packed_indicies()[0] == 2);
	REQUIRE(testPkdVec.get_packed_data()[0] == 126);

	REQUIRE(testPkdVec.get_sparse_vector()[5] == SIZE_MAX);

	testPkdVec.delete_element_at_sparse_vector(9);

	REQUIRE(testPkdVec.get_data_from_sparse_vector(2) == 126);

	testPkdVec.delete_element_at_sparse_vector(2);
}

TEST_CASE("Adding stuff after deleting stuff")
{
	iow::PackedVector<int> testPkdVec(10);
	testPkdVec.add_element_at_sparse_vector(5, 69);
	testPkdVec.add_element_at_sparse_vector(9, 96);
	testPkdVec.add_element_at_sparse_vector(2, 126);
	testPkdVec.delete_element_at_sparse_vector(5);
	testPkdVec.delete_element_at_sparse_vector(9);

	testPkdVec.add_element_at_sparse_vector(4, 999);
	REQUIRE(testPkdVec.get_packed_data()[1] == 999);
}
