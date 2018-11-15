#pragma once
#include <SFML/Graphics.hpp>

namespace iow
{
struct Camera {
	sf::Vector2f position;
	sf::Vector2f scale;

	sf::Vector2f windowsize;
};

} // namespace iow
