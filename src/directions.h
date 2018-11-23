#pragma once
#include <SFML/Graphics.hpp>

namespace iow
{
enum class Directions : unsigned int {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_RIGHT,
	DOWN_RIGHT,
	UP_LEFT,
	DOWN_LEFT,

	INVALID_DIRECTION
};

static inline sf::Vector2f
convertDirectionToNormalizedVector(const Directions n)
{

	switch (n) {
	case Directions::UP:
		return sf::Vector2f(0, 1);
		break;
	case Directions::DOWN:
		return sf::Vector2f(0, -1);
		break;
	case Directions::LEFT:
		return sf::Vector2f(-1, 0);
		break;
	case Directions::RIGHT:
		return sf::Vector2f(1, 0);
		break;
	case Directions::UP_RIGHT:
		return sf::Vector2f(1, 1);
		break;
	case Directions::UP_LEFT:
		return sf::Vector2f(-1, 1);
		break;
	case Directions::DOWN_LEFT:
		return sf::Vector2f(-1, -1);
		break;
	case Directions::DOWN_RIGHT:
		return sf::Vector2f(1, -1);
		break;
	case Directions::INVALID_DIRECTION:
		return sf::Vector2f(0, 0);
		break;
	}
}

} // namespace iow
