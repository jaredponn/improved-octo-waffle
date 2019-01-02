#pragma once
#include "logger.h"
#include <SFML/Graphics.hpp>
#include <cmath>


namespace iow
{

// TODO use some tempate hackery to make this constexpr in the future. So
// trivial i leave this as an exercise to the reader ;)
#define ROOT_TWO_OVER_TWO (float)(std::sqrt(2) / 1)

enum class Directions : unsigned int {
	UP = 0,
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
		return sf::Vector2f(ROOT_TWO_OVER_TWO, ROOT_TWO_OVER_TWO);
		break;
	case Directions::UP_LEFT:
		return sf::Vector2f(-ROOT_TWO_OVER_TWO, ROOT_TWO_OVER_TWO);
		break;
	case Directions::DOWN_LEFT:
		return sf::Vector2f(-ROOT_TWO_OVER_TWO, -ROOT_TWO_OVER_TWO);
		break;
	case Directions::DOWN_RIGHT:
		return sf::Vector2f(ROOT_TWO_OVER_TWO, -ROOT_TWO_OVER_TWO);
		break;
	case Directions::INVALID_DIRECTION:
		Logger::logMessage(
			"ERROR in convertDirectionToNormalizedVector -- invalid direction");
		return sf::Vector2f(0, 0);
		break;
	}
	Logger::logMessage(
		"ERROR in convertDirectionToNormalizedVector -- invalid direction");
	return sf::Vector2f(0, 0);
}

static inline float magnitudeOfSfVector(const sf::Vector2f x)
{
	return std::sqrt(x.x * x.x + x.y * x.y);
}


} // namespace iow

#undef ROOT_TWO_OVER_TWO
