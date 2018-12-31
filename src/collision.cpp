#include "collision.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <optional>
float SignedAreaTriangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	return (a.x - c.x) * (b.y - c.y) * (a.y - c.y) * (b.x - c.x);
}
sf::Vector2f AbsMinBetweenVectors(sf::Vector2f a, sf::Vector2f b, int flag)
{
	// flag = 0, compare X. flag = 1, compare y
	if (flag == 0) { // compare X
		if (std::abs(a.x) < std::abs(b.x)) {
			return a;
		}
		return b;
	}

	// compare Y
	if (std::abs(a.y) < std::abs(b.y)) {
		return a;
	}
	return b;
}

// BIG ERRRRORRRR: this does not (yet) handle 2 moving entities collision.. or
// probably we just move each shape deltax/2 and deltay/2 units back?
//
// entity 2 is wall, and entity 1 is player!!!!!!
std::optional<sf::Vector2f> iow::checkAndResolveCollisionDelta(
	sf::RectangleShape entity1, sf::RectangleShape entity2,
	const sf::Vector2f &direction, const float &speed, const float dt,
	size_t pushFactor)
{

	bool xcollide = false, ycollide = false;
	sf::Vector2f playerCord[] = {
		// x-cords for first 4, then y cords for last 4
		entity1.getPosition(),
		entity1.getPosition()
			+ dt * sf::Vector2f(direction.x, 0) * speed,
		entity1.getPosition() + sf::Vector2f(0, entity1.getSize().y),
		entity1.getPosition() + sf::Vector2f(0, entity1.getSize().y)
			+ dt * sf::Vector2f(direction.x, 0) * speed,

		entity1.getPosition(),
		entity1.getPosition()
			+ dt * sf::Vector2f(0, direction.y) * speed,
		entity1.getPosition() + sf::Vector2f(entity1.getSize().x, 0),
		entity1.getPosition() + sf::Vector2f(entity1.getSize().x, 0)
			+ dt * sf::Vector2f(0, direction.y) * speed};
	sf::Vector2f wallCord[] = {
		// y-cords for first 4, then y cords for last 4
		entity2.getPosition(),
		entity2.getPosition() + sf::Vector2f(0, entity2.getSize().y),
		entity2.getPosition() + sf::Vector2f(entity2.getSize().x, 0),
		entity2.getPosition() + entity2.getSize(),

		entity2.getPosition(),
		entity2.getPosition() + sf::Vector2f(entity2.getSize().x, 0),
		entity1.getPosition() + sf::Vector2f(0, entity1.getSize().y),
		entity1.getPosition() + entity1.getSize()};

	sf::Vector2f shortestXcollidePoint(0, 0),
		shortestYcollidePoint(0, 0); // deafult is 0
	int xColSeg = 0, yColSeg = 0;
	// make sf::vector to store 4 points of 2 lines, when loop..
	size_t tempCounter = -1;
	for (size_t i = 0; i <= 2; i = i + 2) { // first loop the playerCord
		while (tempCounter < (i + 1) * 2 - 1) { // then the wallCord
			tempCounter++;
			// ab is the player seg, cd is wall seg
			float a1 = SignedAreaTriangle(playerCord[i],
						      playerCord[i + 1],
						      wallCord[tempCounter]);
			float a2 = SignedAreaTriangle(
				playerCord[i], playerCord[i + 1],
				wallCord[tempCounter + 1]);
			if (a1 != 0.0f && a2 != 0.0f && a1 * a2 < 0.0f) {
				float a3 = SignedAreaTriangle(
					wallCord[tempCounter + 1],
					wallCord[tempCounter], playerCord[i]);
				float a4 = a3 + a2 - a1;
				if (a3 != 0.0f && a4 != 0.0f
				    && a3 * a4 < 0.0f) {
					// p=a+t(b-a)
					float t = a3 / (a3 - a4);
					sf::Vector2f p =
						playerCord[i]
						+ t
							  * (playerCord[i + 1]
							     - playerCord[i]);
					if (tempCounter < 2) { // comparing X

						xcollide = true;
						shortestXcollidePoint =
							AbsMinBetweenVectors(
								shortestXcollidePoint,
								p, 0);
						xColSeg = tempCounter;
					} else { // comparing Y
						ycollide = true;
						shortestYcollidePoint =
							AbsMinBetweenVectors(
								shortestYcollidePoint,
								p, 1);
						yColSeg = tempCounter;
					}
				}
			}
		}
	}
	if (xcollide && ycollide) {
		// float temp = std::min(deltax, deltay);
		// xColSeg =0 is
		float newDeltaTime = 0;
		if (shortestXcollidePoint == sf::Vector2f(0, 0)
		    || shortestYcollidePoint == sf::Vector2f(0, 0)) {
			if (shortestXcollidePoint == sf::Vector2f(0, 0)) {
				newDeltaTime =
			}

		} else if (deltax == 0 || deltay == 0) {
		} else {
			float temp =
				std::min(std::abs(deltax), std::abs(deltay));
			if (temp == std::abs(deltax)) {
				tempv.x = deltax;
				tempv.y = 0;
			} else {
				tempv.y = deltay;
				tempv.x = 0;
			}
		}
		/*
		std::cout << "collision cocured" << std::endl;
		std::cout << "xcollide = " << xcollide << std::endl;
		std::cout << "entity1 xpos = " << entity1.getPosition().x
			  << std::endl;
		std::cout << "entity1 xpos+size = "
			  << entity1.getPosition().x + entity1.getSize().x
			  << std::endl;
		std::cout << "entity2 xpos = " << entity2.getPosition().x
			  << std::endl;
		std::cout << "entity2 xpos+size = "
			  << entity2.getPosition().x + entity2.getSize().x
			  << std::endl;
		std::cout << "ycollide = " << ycollide << std::endl;
		std::cout << "entity1 ypos = " << entity1.getPosition().y
			  << std::endl;
		std::cout << "entity1 ypos+size = "
			  << entity1.getPosition().y + entity1.getSize().y
			  << std::endl;
		std::cout << "entity2 ypos = " << entity2.getPosition().y
			  << std::endl;
		std::cout << "entity2 ypos+size = "
			  << entity2.getPosition().y + entity2.getSize().y
			  << std::endl;
		std::cout << "deltax " << deltax << std::endl;
		std::cout << "deltay " << deltay << std::endl;
		std::cout << "tempXX " << tempv.x << std::endl;
		std::cout << "tempYY " << tempv.y << std::endl;
		*/
		return std::make_optional(tempv);
	} else {
		return std::nullopt;
	}
}
/*
std::optional<sf::Vector2f>
iow::checkAndResolveCollisionDelta(sf::RectangleShape entity1,
				   sf::RectangleShape entity2,
				   size_t pushFactor)
{


	// entity 2 is wall, and entity 1 is player!!!!!!
	// position start at top left corner, add 0.2f as the bounding box
	bool xcollide = (entity1.getPosition().x + entity1.getSize().x
			 > entity2.sf::Shape::getPosition().x)
			&& (entity2.getPosition().x + entity2.getSize().x
			    > entity1.sf::Shape::getPosition().x);
	bool ycollide = (entity1.getPosition().y + entity1.getSize().y
			 > entity2.sf::Shape::getPosition().y)
			&& (entity2.getPosition().y + entity2.getSize().y
			    > entity1.sf::Shape::getPosition().y);
	float deltax, deltay;
	if (xcollide && ycollide == true) {

		// for x axis
		// if the player is inside the wall's boundary
		if ((entity2.getPosition().x <= entity1.getPosition().x)
		    && (entity2.getPosition().x + entity2.getSize().x
			>= entity1.getPosition().x + entity1.getSize().x)) {
			deltax = 0;
		}
		// if player is to the left of wall
		else if ((entity1.getPosition().x + entity1.getSize().x
			  > entity2.getPosition().x)
			 && (entity1.getPosition().x + entity1.getSize().x
			     < entity2.getPosition().x + entity2.getSize().x)) {
			deltax = entity2.getPosition().x
				 - entity1.getPosition().x - entity1.getSize().x
				 - pushFactor;
		}
		// if player is to the right of wall
		else {
			deltax = entity2.getPosition().x + entity2.getSize().x
				 + pushFactor - entity1.getPosition().x;
		}

		// for y axis

		if ((entity2.getPosition().y <= entity1.getPosition().y)
		    && (entity2.getPosition().y + entity2.getSize().y
			>= entity1.getPosition().y + entity1.getSize().y)) {
			deltay = 0;
		}
		// if player is above the  wall
		else if ((entity1.getPosition().y + entity1.getSize().y
			  > entity2.getPosition().y)
			 && (entity1.getPosition().y + entity1.getSize().y
			     < entity2.getPosition().y + entity2.getSize().y)) {
			deltay = entity2.getPosition().y
				 - entity1.getPosition().y - entity1.getSize().y
				 - pushFactor;

		}
		// if player is below the  wall
		else {
			deltay = entity2.getPosition().y + entity2.getSize().y
				 + pushFactor - entity1.getPosition().y;
		}
		// float temp = std::min(deltax, deltay);
		sf::Vector2f tempv;
		if (deltax == 0 || deltay == 0) {
			tempv.x = deltax;
			tempv.y = deltay;
		} else if (deltax == 0 || deltay == 0) {
		} else {
			float temp =
				std::min(std::abs(deltax), std::abs(deltay));
			if (temp == std::abs(deltax)) {
				tempv.x = deltax;
				tempv.y = 0;
			} else {
				tempv.y = deltay;
				tempv.x = 0;
			}
		}
		std::cout << "collision cocured" << std::endl;
		std::cout << "xcollide = " << xcollide << std::endl;
		std::cout << "entity1 xpos = " << entity1.getPosition().x
			  << std::endl;
		std::cout << "entity1 xpos+size = "
			  << entity1.getPosition().x + entity1.getSize().x
			  << std::endl;
		std::cout << "entity2 xpos = " << entity2.getPosition().x
			  << std::endl;
		std::cout << "entity2 xpos+size = "
			  << entity2.getPosition().x + entity2.getSize().x
			  << std::endl;
		std::cout << "ycollide = " << ycollide << std::endl;
		std::cout << "entity1 ypos = " << entity1.getPosition().y
			  << std::endl;
		std::cout << "entity1 ypos+size = "
			  << entity1.getPosition().y + entity1.getSize().y
			  << std::endl;
		std::cout << "entity2 ypos = " << entity2.getPosition().y
			  << std::endl;
		std::cout << "entity2 ypos+size = "
			  << entity2.getPosition().y + entity2.getSize().y
			  << std::endl;
		std::cout << "deltax " << deltax << std::endl;
		std::cout << "deltay " << deltay << std::endl;
		std::cout << "tempXX " << tempv.x << std::endl;
		std::cout << "tempYY " << tempv.y << std::endl;
return std::make_optional(tempv);
}
else
{
	return std::nullopt;
}
}
*/
bool iow::checkCollisionBullet(sf::CircleShape circle,
			       sf::RectangleShape entity)
{
	sf::Vector2f circleCenter(
		circle.getPosition()
		+ sf::Vector2f(circle.getRadius(), circle.getRadius()));
	sf::Vector2f entityCenter(entity.getPosition()
				  + entity.getSize() / 2.f);
	sf::Vector2f d = circleCenter - entityCenter;
	sf::Vector2f p;
	p.x = std::max(-entity.getSize().x / 2,
		       std::min(d.x, entity.getSize().x / 2))
	      + entityCenter.x;
	p.y = std::max(-entity.getSize().y / 2,
		       std::min(d.y, entity.getSize().y / 2))
	      + entityCenter.y;

	d = p - circleCenter;
	float ptocir = std::sqrt(d.x * d.x + d.y * d.y);
	return ptocir < circle.getRadius();
}
