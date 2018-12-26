#pragma once

#include <SFML/Graphics.hpp>

// https://natureofcode.com/book/chapter-6-autonomous-agents/
struct SteeringBehaviour {
	sf::Vector2f steeringVelocity;

	sf::Vector2f desiredVelocity; //  = target - location
	float maxSpeed; // normalize desired velocity, then multiply by max
			// speed
};
