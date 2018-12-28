#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

// anon namespace
namespace
{

float absVec(sf::Vector2f val)
{
	return std::sqrt((val.x * val.x) + (val.y * val.y));
}

sf::Vector2f normalizeVec(sf::Vector2f val)
{
	sf::Vector2f normalizedVec;
	const float vecmagnitude = absVec(val);
	// TODO probably the cause of the bugge behavior
	if (vecmagnitude == 0)
		return sf::Vector2f{0, 0};

	// TODO probably the cause of the bugge behavior
	normalizedVec.x = val.x / vecmagnitude;
	normalizedVec.y = val.y / vecmagnitude;

	return normalizedVec;
}
} // namespace

namespace iow
{

namespace SteeringBehaviour
{

// https://natureofcode.com/book/chapter-6-autonomous-agents/
struct SteeringBehaviour {
	float maxSpeed; // max speed of steering behaviour

	float fleeRadius; // radius to be when fleeing form another thing
};

static inline sf::Vector2f
calculateSeekSteeringVelocity(const SteeringBehaviour steeringBehaviourAttr,
			      const sf::Vector2f currentVelocity,
			      const sf::Vector2f positionDelta)
{

	sf::Vector2f steeringVelocity;

	sf::Vector2f desiredVelocity =
		normalizeVec(positionDelta) * steeringBehaviourAttr.maxSpeed;

	steeringVelocity = desiredVelocity - currentVelocity;

	return steeringVelocity;
}

static inline sf::Vector2f calculatePositionDelta(const sf::Vector2f a,
						  const sf::Vector2f b)
{
	return a - b;
}

static inline sf::Vector2f
calculateFleeVelocity(const SteeringBehaviour steeringBehaviourAttr,
		      const sf::Vector2f currentVelocity,
		      const sf::Vector2f positionDelta)
{
	if (absVec(positionDelta) <= steeringBehaviourAttr.fleeRadius) {
		return calculateSeekSteeringVelocity(
			steeringBehaviourAttr, currentVelocity, -positionDelta);
	}
	return sf::Vector2f{0, 0};
}


} // namespace SteeringBehaviour


} // namespace iow
