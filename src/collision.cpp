#include "collision.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <optional>
// BIG ERRRRORRRR: this does not (yet) handle 2 moving entities collision.. or
// probably we just move each shape deltax/2 and deltay/2 units back?
std::optional<sf::Vector2f>
iow::checkAndResolveCollisionDelta(sf::RectangleShape entity1,
				   sf::RectangleShape entity2)
{
	// entity 2 is wall, and entity 1 is player!!!!!!
	//
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
	// std::cout << "ycollide = " << ycollide << std::endl;
	//

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
				 - entity1.getPosition().x
				 - entity1.getSize().x;
		}
		// if player is to the right of wall
		else {
			deltax = entity2.getPosition().x + entity2.getSize().x
				 - entity1.getPosition().x;
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
				 - entity1.getPosition().y
				 - entity1.getSize().y;

		}
		// if player is below the  wall
		else {
			deltay = entity2.getPosition().y + entity2.getSize().y
				 - entity1.getPosition().y;
		}
		// float temp = std::min(deltax, deltay);
		sf::Vector2f tempv;
		if (deltax == 0 || deltay == 0) {
			tempv.x = deltax;
			tempv.y = deltay;
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

bool iow::checkCollision(sf::CircleShape circle, sf::RectangleShape entity)
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
