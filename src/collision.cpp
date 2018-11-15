#include <SFML/Graphics.hpp>
#include <iostream>
#include "collision.h"
#include <cmath>
#include <optional>
// BIG ERRRRORRRR: this does not (yet) handle 2 moving entities collision.. or
// probably we just move each shape deltax/2 and deltay/2 units back?
std::optional<sf::Vector2f> iow::checkCollision(sf::RectangleShape entity1,
						sf::RectangleShape entity2)
{
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
	if (xcollide && ycollide == true) // they collide
	{
		sf::Vector2f entity1Center = sf::Vector2(
			entity1.getPosition().x + entity1.getSize().x / 2,
			entity1.getPosition().y + entity1.getSize().y / 2);
		if (entity2.getPosition().x + entity2.getSize().x
		    < entity1Center.x) // if entity 2 is to the left of
				       // entity 1's center
		{
			deltax = (entity2.getPosition().x + entity2.getSize().x)
				 - entity1.getPosition().x;
		} else // if entity 2 is to the
		       // right of entity 1's center
		{
			deltax = (entity1.getPosition().x + entity1.getSize().x)
				 - entity2.getPosition().x;
		}
		if (entity2.getPosition().y + entity2.getSize().y
		    < entity1Center.y) // if entity 2 is to the left of
				       // entity 1's center
		{
			deltay = (entity2.getPosition().y + entity2.getSize().y)
				 - entity1.getPosition().y
				 - entity1.getSize().y;
		} else // if entity 2 is to the right
		       // of entity 1's center
		{


			deltay = (entity1.getPosition().y + entity1.getSize().y)
				 - entity2.getPosition().y
				 - entity2.getSize().y;
		}
		float temp = std::min(deltax, deltay);
		sf::Vector2f tempv;
		if (temp == deltax) {
			tempv.x = temp;
			tempv.y = 0;
		} else {
			tempv.y = temp;
			tempv.x = 0;
		}
		// UNHANDLED THOUGHTS: what if they collide diagonally?
		return std::make_optional(tempv);
	} else {
		return std::nullopt;
	}
}

bool iow::checkCollision(sf::CircleShape circle, sf::RectangleShape entity)
{
	// the circle' position is its center
	sf::Vector2f circleCenter = circle.getPosition();
	sf::Vector2f entityCenter = entity.getPosition();
	entityCenter.x = entityCenter.x + entity.getSize().x / 2 + 0.2f;
	entityCenter.y = entityCenter.y + entity.getSize().y / 2 + 0.2f;
	sf::Vector2f d = circleCenter - entityCenter;
	sf::Vector2f p;
	p.x = std::max(-entity.getSize().x / 2 - 0.2f,
		       std::min(d.x, entity.getSize().x / 2 + 0.2f));
	p.y = std::max(-entity.getSize().y / 2 - 0.2f,
		       std::min(d.y, entity.getSize().y / 2 + 0.2f));
	d = p - circleCenter;
	float ptocir = std::sqrt(p.x * p.x + p.y * p.y);
	return ptocir < circle.getRadius();
}
