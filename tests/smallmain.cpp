#include "../src/graph.h"
#include "../src/pathfinding.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>

int main(void)
{
	sf::RectangleShape a{sf::Vector2f(32, 32)};

	std::cout << a.getSize().x << ", " << a.getSize().y << std::endl;

	return 0;
}
