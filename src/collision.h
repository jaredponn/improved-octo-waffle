#pragma once
#include "position.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

namespace iow
{

/*
 * get the updated position
 * checks if there is a collision
 *time is micro seconds
 */

using CollisionBox = sf::RectangleShape;
using CollisionCir = sf::CircleShape;

// checks collision between 2 rectangles
std::optional<sf::Vector2f> checkAndResolveCollisionPlayerWithWall(
	CollisionBox entity1, CollisionBox entity2,
	const sf::Vector2f &velocity, const sf::Vector2f &prevVelocity,
	const float dt, float &playerDeltaTime, size_t pushfactor = 0);

// checks collision between a circle and a rectangle
bool checkCollisionBullet(sf::CircleShape entity1, sf::RectangleShape entity2);

static inline iow::CollisionBox
setCollisionBoxPositionFromPosition(const iow::CollisionBox &collisionbox,
				    const iow::Position &pos)
{
	auto tmp = collisionbox;
	tmp.setPosition(pos);
	return tmp;
}

static inline iow::Position getCollisionBoxCenter(CollisionBox const &box)
{
	sf::Vector2f const size = box.getSize();
	iow::Position const pos = box.getPosition();

	return sf::Vector2f{pos.x + size.x / 2.f, pos.y + size.y / 2.f};
}


} // namespace iow
