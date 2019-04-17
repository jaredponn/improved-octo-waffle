#include "collision.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <optional>
double SignedAreaTriangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
sf::Vector2f AbsMinBetweenVectors(sf::Vector2f a, sf::Vector2f b,
				  sf::Vector2f size, int flag)
{
	// flag = 0, compare X. flag = 1, compare y
	if (flag == 0) { // compare X
		if (std::abs(a.x) < std::abs(b.x)) {
			return size - a;
		}
		return size - b;
	}

	// compare Y
	if (std::abs(a.y) < std::abs(b.y)) {
		return size - a;
	}
	return size - b;
}
float calculateXdistance(const sf::Vector2f &velocity,
			 const sf::Vector2f &prevVelocity, const float min1,
			 const float min2)
{

	float temp = std::min(std::abs(min1), std::abs(min2));
	std::cout << "float temp = " << temp << std::endl;
	if (velocity.x < 0) { // going left
		return temp;
		if (temp == std::abs(min1)) {
			if (min1 > 0) {
				return temp; //+ pushfactor
			} else {
				return -temp; //+ pushfactor
			}
		} else {

			if (min2 > 0) {
				return temp; //+ pushfactor
			} else {
				return -temp; //+ pushfactor
			}
		}
	} else if (velocity.x > 0) { // going right
		return -temp;
		if (temp == std::abs(min1)) {
			if (min1 > 0) {
				return -temp;
			} else {
				return temp;
			}
		} else {

			if (min2 > 0) {
				return -temp;
			} else {
				return temp;
			}
		}
	} else { // special case when player stops moving, need to resolve the
		 // collision
		if (prevVelocity.x < 0) {

			// to be negative.
			if (temp == std::abs(min1)) {
				return temp;
				if (min1 > 0) {
					return temp; //+
						     // pushfactor
				} else {
					return -temp; //+
						      // pushfactor
				}
			} else {
				if (min2 > 0) {
					return temp; //+
						     // pushfactor
				} else {
					return -temp; //+
						      // pushfactor
				}
			}
		} else if (prevVelocity.x > 0) {

			return -temp;
			if (temp == std::abs(min1)) {
				if (min1 > 0) {
					return -temp;
					// - pushfactpr
				} else {
					return temp;
				}
			} else {

				if (min2 > 0) {
					return -temp;
				} else {
					return temp;
				}
			}
		} else {
			return 0;
		}
	}
}

float calculateYdistance(const sf::Vector2f &velocity,
			 const sf::Vector2f &prevVelocity, const float min1,
			 const float min2)
{

	float temp = std::min(std::abs(min1), std::abs(min2));
	std::cout << "float temp = " << temp << std::endl;
	if (velocity.y < 0) { // going down
		return temp;
		if (temp == std::abs(min1)) {
			if (min1 > 0) {
				return -temp; //+ pushfactor
			} else {
				return temp; //+ pushfactor
			}
		} else {

			if (min2 > 0) {
				return -temp; //+ pushfactor
			} else {
				return temp; //+ pushfactor
			}
		}
	} else if (velocity.y > 0) { // going up
		return -temp;
		if (temp == std::abs(min1)) {
			if (min1 > 0) {
				return temp;
			} else {
				return -temp;
			}
		} else {

			if (min2 > 0) {
				return temp;
			} else {
				return -temp;
			}
		}
	}

	else { // special case when player stops moving, need to resolve the
	       // collision
		if (prevVelocity.y < 0) {

			return temp;
			// to be negative.
			if (temp == std::abs(min1)) {
				if (min1 > 0) {
					return -temp; //+
						      // pushfactor
				} else {
					return temp; //+
						     // pushfactor
				}
			} else {
				if (min2 > 0) {
					return -temp; //+
						      // pushfactor
				} else {
					return temp; //+
						     // pushfactor
				}
			}
		} else if (prevVelocity.y > 0) {

			return -temp;
			if (temp == std::abs(min1)) {
				if (min1 > 0) {
					return temp;
					// - pushfactpr
				} else {
					return -temp;
				}
			} else {

				if (min2 > 0) {
					return temp;
				} else {
					return -temp;
				}
			}
		} else {
			return 0;
		}
	}
}
float calculateEpsilon(const sf::RectangleShape entity1,
		       const sf::RectangleShape entity2, const float &velocity,
		       const int flag)
{
	const float EPSILON = 0.005;
	if (flag == 0) { // flag = 0 will hanndle X direction
		if ((entity2.getPosition().x <= entity1.getPosition().x)
		    && (entity2.getPosition().x + entity2.getSize().x
			>= entity1.getPosition().x + entity1.getSize().x)) {
			return 0;
		}
		// if player is to the left of wall
		else if ((entity1.getPosition().x + entity1.getSize().x
			  > entity2.getPosition().x)
			 && (entity1.getPosition().x + entity1.getSize().x
			     < entity2.getPosition().x + entity2.getSize().x)) {

			// NEG!!
			if (velocity < 0) { // going left
				return -EPSILON;
			} else if (velocity > 0) { // going right
				return EPSILON;
			} else {
				return 0;
			}
		}
		// if player is to the right of wall
		else {
			if (velocity < 0) { // going left
				return EPSILON;
			} else if (velocity > 0) { // going right
				return -EPSILON;
			} else {
				return 0;
			}
		}


	} else {

		if ((entity2.getPosition().y <= entity1.getPosition().y)
		    && (entity2.getPosition().y + entity2.getSize().y
			>= entity1.getPosition().y + entity1.getSize().y)) {
			return 0;
		}
		// if player is above the  wall
		else if ((entity1.getPosition().y + entity1.getSize().y
			  > entity2.getPosition().y)
			 && (entity1.getPosition().y + entity1.getSize().y
			     < entity2.getPosition().y + entity2.getSize().y)) {
			if (velocity < 0) { // going left
				return EPSILON;
			} else if (velocity > 0) { // going right
				return -EPSILON;
			} else {
				return 0;
			}
		}
		// if player is below the  wall
		else {
			// NEG!!
			if (velocity < 0) { // going left
				return -EPSILON;
			} else if (velocity > 0) { // going right
				return EPSILON;
			} else {
				return 0;
			}
		}
	}
}
bool checkBruteForceCollision(const sf::RectangleShape entity1,
			      const sf::RectangleShape &entity2)
{

	// Collision x-axis?
	bool collisionX = entity1.getPosition().x + entity1.getSize().x
				  > entity2.getPosition().x
			  && entity2.getPosition().x + entity2.getSize().x
				     > entity1.getPosition().x;
	// Collision y-axis?
	bool collisionY = entity1.getPosition().y + entity1.getSize().y
				  > entity2.getPosition().y
			  && entity2.getPosition().y + entity2.getSize().y
				     > entity1.getPosition().y;
	// Collision only if on both axes
	return collisionX && collisionY;
}
bool checkCollision(const sf::RectangleShape &entity1,
		    const sf::RectangleShape &entity2,
		    const sf::Vector2f &velocity, const float dt)
{

	bool xcollide = false, ycollide = false;
	std::vector<sf::Vector2f> playerCord;
	if (velocity.x < 0) { // left
		playerCord.push_back(entity1.getPosition()
				     + dt * sf::Vector2f(velocity.x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y)
				     + dt * sf::Vector2f(velocity.x, 0));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	} else if (velocity.x > 0) { // right
		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0)
				     + dt * sf::Vector2f(velocity.x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition() + entity1.getSize()
				     + dt * sf::Vector2f(velocity.x, 0));
	} else { // v is 0

		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	}


	if (velocity.y < 0) { // going down
		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y)
				     + dt * sf::Vector2f(0, velocity.y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition() + entity1.getSize()
				     + dt * sf::Vector2f(0, velocity.y));
	} else if (velocity.y > 0) { // going up
		playerCord.push_back(entity1.getPosition()
				     + dt * sf::Vector2f(0, velocity.y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0)
				     + dt * sf::Vector2f(0, velocity.y));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	} else {
		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	}

	std::vector<sf::Vector2f> wallCord = {
		// y-cords for first 4, then x cords for last 4
		entity2.getPosition(),
		entity2.getPosition() + sf::Vector2f(0, entity2.getSize().y),
		entity2.getPosition() + sf::Vector2f(entity2.getSize().x, 0),
		entity2.getPosition() + entity2.getSize(),

		entity2.getPosition(),
		entity2.getPosition() + sf::Vector2f(entity2.getSize().x, 0),
		entity2.getPosition() + sf::Vector2f(0, entity2.getSize().y),
		entity2.getPosition() + entity2.getSize()};


	sf::Vector2f closestXcollidePoint(0, 0),
		closestYcollidePoint(0, 0); // deafult is 0
	std::vector<sf::Vector2f> xcollidePoints, ycollidePoints;


	for (size_t i = 0; i <= 6; i = i + 2) { // first loop the playerCord
		int originalTempCounter, tempCounter;
		if (i < 4) {
			tempCounter = 0;
		} else {
			tempCounter = 4;
		}
		originalTempCounter = tempCounter;
		while (tempCounter
		       < originalTempCounter + 4) { // then the wallCord
			// ab is the player seg, cd is wall seg
			// a,b,d
			float a1 = SignedAreaTriangle(playerCord[i],
						      playerCord[i + 1],
						      wallCord[tempCounter]);
			// a,b,c
			float a2 = SignedAreaTriangle(
				playerCord[i], playerCord[i + 1],
				wallCord[tempCounter + 1]);
			if (a1 != 0.0f && a2 != 0.0f && ((a1 * a2) < 0.0f)) {
				float a3 = SignedAreaTriangle(
					wallCord[tempCounter + 1],
					wallCord[tempCounter], playerCord[i]);
				float a4 = a3 + a2 - a1;
				std::cout << "a1 =" << a1 << "a2 =" << a2
					  << "a3 =" << a3 << "a4 =" << a4
					  << std::endl;
				if (a3 != 0.0f && a4 != 0.0f
				    && ((a3 * a4) < 0.0f)) {
					// p=a+t(b-a)

					float t = a3 / (a3 - a4);
					sf::Vector2f p = sf::Vector2f(
						playerCord[i]
						+ t
							  * (playerCord[i + 1]
							     - playerCord[i]));

					if (tempCounter < 4) { // comparing X
						xcollide = true;
						xcollidePoints.push_back(
							p); // stores
							    // the x
							    // collision
							    // cords
					} else {	    // comparing Y

						ycollide = true;
						ycollidePoints.push_back(
							p); // stores
							    // the y
							    // collision
							    // cords
					}
				}
			}

			tempCounter = tempCounter + 2;
		}
	}
	return xcollide || ycollide;
}

// BIG ERRRRORRRR: this does not (yet) handle 2 moving entities collision.. or
// probably we just move each shape deltax/2 and deltay/2 units back?
//
// entity 2 is wall, and entity 1 is player!!!!!!
std::optional<sf::Vector2f> iow::checkAndResolveCollisionPlayerWithWall(
	sf::RectangleShape &entity1, const sf::RectangleShape &entity2,
	const sf::Vector2f &velocity, const sf::Vector2f &prevVelocity,
	const float &dt, float &playerDeltaTime, sf::Vector2f &playerPosition,
	size_t pushFactor)
{

	pushFactor = 1;
	bool xcollide = false, ycollide = false;
	std::vector<sf::Vector2f> playerCord;
	if (velocity.x < 0) { // left
		playerCord.push_back(entity1.getPosition()
				     + dt * sf::Vector2f(velocity.x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y)
				     + dt * sf::Vector2f(velocity.x, 0));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	} else if (velocity.x > 0) { // right
		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0)
				     + dt * sf::Vector2f(velocity.x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition() + entity1.getSize()
				     + dt * sf::Vector2f(velocity.x, 0));
	} else { // v is 0

		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	}


	if (velocity.y < 0) { // going down
		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y)
				     + dt * sf::Vector2f(0, velocity.y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition() + entity1.getSize()
				     + dt * sf::Vector2f(0, velocity.y));
	} else if (velocity.y > 0) { // going up
		playerCord.push_back(entity1.getPosition()
				     + dt * sf::Vector2f(0, velocity.y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0)
				     + dt * sf::Vector2f(0, velocity.y));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	} else {
		playerCord.push_back(entity1.getPosition());
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(0, entity1.getSize().y));
		playerCord.push_back(entity1.getPosition()
				     + sf::Vector2f(entity1.getSize().x, 0));
		playerCord.push_back(entity1.getPosition() + entity1.getSize());
	}

	std::vector<sf::Vector2f> wallCord = {
		// y-cords for first 4, then x cords for last 4
		entity2.getPosition(),
		entity2.getPosition() + sf::Vector2f(0, entity2.getSize().y),
		entity2.getPosition() + sf::Vector2f(entity2.getSize().x, 0),
		entity2.getPosition() + entity2.getSize(),

		entity2.getPosition(),
		entity2.getPosition() + sf::Vector2f(entity2.getSize().x, 0),
		entity2.getPosition() + sf::Vector2f(0, entity2.getSize().y),
		entity2.getPosition() + entity2.getSize()};


	sf::Vector2f closestXcollidePoint(0, 0),
		closestYcollidePoint(0, 0); // deafult is 0
	std::vector<sf::Vector2f> xcollidePoints, ycollidePoints;


	for (size_t i = 0; i <= 6; i = i + 2) { // first loop the playerCord
		int originalTempCounter, tempCounter;
		if (i < 4) {
			tempCounter = 0;
		} else {
			tempCounter = 4;
		}
		originalTempCounter = tempCounter;
		while (tempCounter
		       < originalTempCounter + 4) { // then the wallCord
			// ab is the player seg, cd is wall seg
			// a,b,d
			float a1 = SignedAreaTriangle(playerCord[i],
						      playerCord[i + 1],
						      wallCord[tempCounter]);
			// a,b,c
			float a2 = SignedAreaTriangle(
				playerCord[i], playerCord[i + 1],
				wallCord[tempCounter + 1]);
			if (a1 != 0.0f && a2 != 0.0f && ((a1 * a2) < 0.0f)) {
				float a3 = SignedAreaTriangle(
					wallCord[tempCounter + 1],
					wallCord[tempCounter], playerCord[i]);
				float a4 = a3 + a2 - a1;
				// std::cout << "a1 =" << a1 << "a2 =" << a2
				//<< "a3 =" << a3 << "a4 =" << a4
				//<< std::endl;
				if (a3 != 0.0f && a4 != 0.0f
				    && ((a3 * a4) < 0.0f)) {
					// p=a+t(b-a)

					float t = a3 / (a3 - a4);
					sf::Vector2f p = sf::Vector2f(
						playerCord[i]
						+ t
							  * (playerCord[i + 1]
							     - playerCord[i]));

					if (tempCounter < 4) { // comparing X
						xcollide = true;
						xcollidePoints.push_back(
							p); // stores
							    // the x
							    // collision
							    // cords
					} else {	    // comparing Y

						ycollide = true;
						ycollidePoints.push_back(
							p); // stores
							    // the y
							    // collision
							    // cords
					}
				}
			}

			tempCounter = tempCounter + 2;
		}
	}
	/*

	for (size_t i = 0; i < wallCord.size(); ++i) {
		std::cout << " wall cord " << i << " = " << wallCord[i].x << " "
			  << wallCord[i].y << std::endl;
		;
	}

	for (size_t i = 0; i < playerCord.size(); ++i) {
		std::cout << "player cord " << i << " = " << playerCord[i].x
			  << " " << playerCord[i].y << std::endl;
		;
	}
	*/
	if (xcollide || ycollide) { // if either collide..

		std::cout << "Velocity in collision.cPP = " << velocity.x << " "
			  << velocity.y << std::endl;

		if (ycollide == true) {
			std::cout << "ycollide " << ycollide << std::endl;
		}

		if (xcollide == true) {
			std::cout << "xcollide " << xcollide << std::endl;
		}
		// float temp = std::min(deltax, deltay);
		std::cout << "prev speed " << prevVelocity.x << " "
			  << prevVelocity.y << std::endl;

		for (size_t i = 0; i < xcollidePoints.size(); ++i) {
			std::cout << " xcollide point " << i << " = "
				  << xcollidePoints[i].x << " "
				  << xcollidePoints[i].y << std::endl;
			;
		}
		for (size_t i = 0; i < ycollidePoints.size(); ++i) {
			std::cout << " ycollide point " << i << " = "
				  << ycollidePoints[i].x << " "
				  << ycollidePoints[i].y << std::endl;
			;
		}
		sf::Vector2f newVelocity = sf::Vector2f(0, 0);
		float ydistanceMove = 0, xdistanceMove = 0;

		if (ycollidePoints.size() > 0) { // calculate ydistanceMove
			if (ycollidePoints.size() == 2) {
				closestYcollidePoint = AbsMinBetweenVectors(
					entity1.getPosition()
						- ycollidePoints[0],
					entity1.getPosition()
						- ycollidePoints[1],
					entity1.getPosition(), 1);
			} else if (ycollidePoints.size() == 1) {
				closestYcollidePoint = ycollidePoints[0];
			}


			float min1 = entity1.getPosition().y
				     - closestYcollidePoint.y,
			      min2 = entity1.getPosition().y
				     + entity1.getSize().y
				     - closestYcollidePoint.y;

			std::cout << " entity1.getPosition().y  = "
				  << entity1.getPosition().y << std::endl;
			std::cout
				<< " entity1.getPosition().y + entity1.getSize().y = "
				<< entity1.getPosition().y + entity1.getSize().y
				<< std::endl;
			std::cout << "y min 1 = " << min1 << std::endl;
			std::cout << "y min 2 = " << min2 << std::endl;
			ydistanceMove = calculateYdistance(
				velocity, prevVelocity, min1, min2);
		}

		if (xcollidePoints.size() > 0) { // calculate xdistanceMove
			if (xcollidePoints.size() == 2) {
				closestXcollidePoint = AbsMinBetweenVectors(
					entity1.getPosition()
						- xcollidePoints[0],
					entity1.getPosition()
						- xcollidePoints[1],
					entity1.getPosition(), 0);
			} else {
				closestXcollidePoint = xcollidePoints[0];
			}
			float min1 = entity1.getPosition().x
				     - closestXcollidePoint.x,
			      min2 = entity1.getPosition().x
				     + entity1.getSize().x
				     - closestXcollidePoint.x;
			std::cout << " entity1.getPosition().x  = "
				  << entity1.getPosition().x << std::endl;
			std::cout
				<< " entity1.getPosition().x + entity1.getSize().x = "
				<< entity1.getPosition().x + entity1.getSize().x
				<< std::endl;
			std::cout << "x min 1 = " << min1 << std::endl;
			std::cout << "x min 2 = " << min2 << std::endl;
			// magic lmfao
			xdistanceMove = calculateXdistance(
				velocity, prevVelocity, min1, min2);

			// std::cout << "min 1 = " << min1 << std::endl;
			// std::cout << "min 2 = " << min2 << std::endl;
		}
		/*
		std::cout << "closestXcollidePoint.x = "
			  << closestXcollidePoint.x << std::endl;
		std::cout << "xdistanceMove = " << xdistanceMove << std::endl;
		std::cout << "ydistanceMove = " << ydistanceMove << std::endl;
		std::cout << "dt  = " << dt << std::endl;
		*/


		/*
		bool xcollide =
			(entity1.getPosition().x + entity1.getSize().x
			 > entity2.sf::Shape::getPosition().x)
			&& (entity2.getPosition().x
				    + entity2.getSize().x
			    > entity1.sf::Shape::getPosition().x);
		bool ycollide =
			(entity1.getPosition().y + entity1.getSize().y
			 > entity2.sf::Shape::getPosition().y)
			&& (entity2.getPosition().y
				    + entity2.getSize().y
			    > entity1.sf::Shape::getPosition().y);

		if (xdistanceMove == 0) {

			newVelocity =
				velocity * dt
				+ (sf::Vector2f(0, ydistanceMove));
			std::cout << "diagonal new  velocity = "
				  << newVelocity.x << ", "
				  << newVelocity.y << std::endl;
			playerDeltaTime = 1;
			// newVelocity =
			// velocity
			//+ (sf::Vector2f(0, ydistanceMove)) / dt;

		} else if (ydistanceMove == 0) {

			newVelocity =
				velocity * dt
				+ (sf::Vector2f(xdistanceMove, 0));
			std::cout << "diagonal new  velocity = "
				  << newVelocity.x << ", "
				  << newVelocity.y << std::endl;
			playerDeltaTime = 1;
			// newVelocity =
			// velocity
			//+ (sf::Vector2f(xdistanceMove, 0)) / dt;
		} else {
			std::cout << "xcollide = " << xcollide
				  << " , ycolldie = " << ycollide
				  << std::endl;
			if (ycollide) {


				newVelocity =
					velocity * dt
					+ (sf::Vector2f(0,
							ydistanceMove));
				std::cout
					<< "diagonal DOUBLE new velocity
		= "
					<< newVelocity.x << ", "
					<< newVelocity.y << std::endl;
				playerDeltaTime = 1;
				// newVelocity =
				// velocity
				//+ (sf::Vector2f(xdistanceMove,
				// 0))
				/// dt;
			} else {

				newVelocity =
					velocity * d
					+ (sf::Vector2f(xdistanceMove,
							0));
				std::cout
					<< "diagonal DOUBLE new velocity
		= "
					<< newVelocity.x << ", "
					<< newVelocity.y << std::endl;
				playerDeltaTime = 1;
				// newVelocity =
				// velocity
				//+ (sf::Vector2f(0,
				// ydistanceMove))
				/// dt;
			}
		}
		*/

		float temp;
		if (xdistanceMove == 0 || ydistanceMove == 0) { // if both are


			for (size_t i = 0; i < wallCord.size(); ++i) {
				std::cout << " wall cord " << i << " = "
					  << wallCord[i].x << " "
					  << wallCord[i].y << std::endl;
				;
			}

			for (size_t i = 0; i < playerCord.size(); ++i) {
				std::cout << "player cord " << i << " = "
					  << playerCord[i].x << " "
					  << playerCord[i].y << std::endl;
				;
			}

			for (size_t i = 0; i < xcollidePoints.size(); ++i) {
				std::cout << " xcollide point " << i << " = "
					  << xcollidePoints[i].x << " "
					  << xcollidePoints[i].y << std::endl;
				;
			}
			for (size_t i = 0; i < ycollidePoints.size(); ++i) {
				std::cout << " ycollide point " << i << " = "
					  << ycollidePoints[i].x << " "
					  << ycollidePoints[i].y << std::endl;
				;
			}
			std::cout << "xdistanceMove = " << xdistanceMove
				  << std::endl;
			std::cout << "ydistanceMove = " << ydistanceMove
				  << std::endl;
			std::cout
				<< " (xdistanceMove == 0)!= (ydistanceMove == 0)"
				<< ((xdistanceMove == 0)
				    != (ydistanceMove == 0))
				<< std::endl;
			if (velocity != sf::Vector2f(0, 0)) {
				if ((xdistanceMove == 0)
				    != (ydistanceMove == 0)) {
					if (xdistanceMove == 0) {
						newVelocity = (sf::Vector2f(
							velocity.x * dt,
							ydistanceMove));
					} else if (ydistanceMove == 0) {
						newVelocity = (sf::Vector2f(
							xdistanceMove,
							velocity.y * dt));
					}

					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					sf::RectangleShape tempEntity1;
					tempEntity1.setSize(entity1.getSize());
					tempEntity1.setPosition(
						entity1.getPosition()
						+ newVelocity);
					bool stillCollide = checkCollision(
						tempEntity1, entity2, velocity,
						dt);


					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					if (stillCollide) {
						std::cout
							<< "in NOT BOTH 0 ydirCol and xdirCol!!!!"
							<< std::endl;

						std::cout
							<< "playerpos moving x direction: = "
							<< (playerPosition
							    + sf::Vector2f(
								      velocity.x,
								      newVelocity
									      .y))
								   .x
							<< " "
							<< (playerPosition
							    + sf::Vector2f(
								      velocity.x,
								      newVelocity
									      .y))
								   .y
							<< std::endl;

						std::cout
							<< "playerpos moving y direction: = "
							<< (playerPosition
							    + sf::Vector2f(
								      newVelocity
									      .x,
								      velocity.y
									      * dt))
								   .x
							<< " "
							<< (playerPosition
							    + sf::Vector2f(
								      newVelocity
									      .x,
								      velocity.y
									      * dt))
								   .y
							<< std::endl;
						sf::RectangleShape tempXentity1,
							tempYentity1;

						tempXentity1.setSize(
							entity1.getSize());
						tempYentity1.setSize(
							entity1.getSize());
						tempXentity1.setPosition(
							entity1.getPosition());
						tempYentity1.setPosition(
							entity1.getPosition());
						std::cout
							<< "first checkCollision = "
							<< !checkCollision(
								   tempXentity1,
								   entity2,
								   sf::Vector2f(
									   velocity.x,
									   newVelocity.y
										   / dt),
								   dt)
							<< ", second checkCollision = "
							<< !checkCollision(
								   tempYentity1,
								   entity2,
								   sf::Vector2f(
									   newVelocity.x
										   / dt,
									   velocity.y),
								   dt)
							<< std::endl;
						/*
						if
						(!checkCollision(tempXonlyEntity1,
								    entity2)) {
							newVelocity =
						sf::Vector2f( xdistanceMove, 0);
						} else if (!checkCollision(
								   tempYonlyEntity1,
								   entity2)) {
							newVelocity =
						sf::Vector2f( 0, ydistanceMove);
						}
					   */
						if (!checkCollision(
							    tempXentity1,
							    entity2,
							    sf::Vector2f(
								    velocity.x,
								    newVelocity.y
									    / dt),
							    dt)) { // check
								   // only
							// move in x
							// direction
							newVelocity = sf::Vector2f(
								velocity.x * dt,
								newVelocity.y);
						} else if (
							!checkCollision(
								tempYentity1,
								entity2,
								sf::Vector2f(
									newVelocity.x
										/ dt,
									velocity.y),
								dt)) { // check
								       // only
							// move in y
							// direction
							newVelocity = sf::Vector2f(
								newVelocity.x,
								velocity.y
									* dt);
						}

						else {
							/*
						newVelocity = sf::Vector2f(
							calculateEpsilon(
								entity1,
								entity2,
								velocity.x,
								0),
							calculateEpsilon(
								entity1,
								entity2,
								velocity.y,
								1));
						*/
							sf::Vector2f tempNewVelocity = sf::Vector2f(
								calculateEpsilon(
									entity1,
									entity2,
									velocity.x,
									0),
								calculateEpsilon(
									entity1,
									entity2,
									velocity.y,
									1));
							sf::RectangleShape
								tempPlayer;
							tempPlayer.setSize(
								entity1.getSize());
							tempEntity1.setPosition(
								playerPosition
								+ tempNewVelocity);

							if (checkBruteForceCollision(
								    tempPlayer,
								    entity2)) {


								newVelocity =
									tempNewVelocity;
							}


							/*
							if (playerPosition.x
									    +
							tempNewVelocity .x
								    <=
							playerPosition.x
									       + newVelocity
											 .x
							    && playerPosition.y
									       + newVelocity
											 .y
								       <=
							playerPosition.y
										  + newVelocity
											    .y) {
								newVelocity =
									tempNewVelocity;
							}
							*/
						}

						/*
						else {
							newVelocity =
								sf::Vector2f(0,
						0);
						}
						*/
					}


				} else { // both x and y distance = 0

					std::cout << "in velocity both 0!!"
						  << std::endl;
					sf::RectangleShape tempXonlyEntity1,
						tempYonlyEntity1;
					tempXonlyEntity1.setSize(
						entity1.getSize());
					tempYonlyEntity1.setSize(
						entity1.getSize());

					tempXonlyEntity1.setPosition(
						entity1.getPosition());

					tempYonlyEntity1.setPosition(
						entity1.getPosition());

					std::cout
						<< "in BOTH 0 "
						<< "xonly checkCollision= "
						<< !checkCollision(
							   tempXonlyEntity1,
							   entity2,
							   sf::Vector2f(
								   velocity.x,
								   0),
							   dt)

						<< "yonly checkCollision= "
						<< !checkCollision(
							   tempYonlyEntity1,
							   entity2,
							   sf::Vector2f(
								   0,
								   velocity.y),
							   dt)
						<< std::endl;

					if (!checkCollision(
						    tempYonlyEntity1, entity2,
						    sf::Vector2f(0, velocity.y),
						    dt)) {
						newVelocity = sf::Vector2f(
							0, velocity.y * dt);
					} else if (!checkCollision(
							   tempXonlyEntity1,
							   entity2,
							   sf::Vector2f(
								   velocity.x,
								   0),
							   dt)) {
						newVelocity = sf::Vector2f(
							velocity.x * dt, 0);
					}
					/*
					else {
							newVelocity =
								sf::Vector2f(0,
									     0);
						}
						*/
				}


				/*
				else {
					newVelocity = sf::Vector2f(0, 0);
				}

				*/

				std::cout << "player position after adding "
					  << (playerPosition + newVelocity).x
					  << " "
					  << (playerPosition + newVelocity).y
					  << std::endl;

			} else {

				if ((xdistanceMove == 0)
				    != (ydistanceMove == 0)) {
					if (xdistanceMove == 0) {
						newVelocity = (sf::Vector2f(
							prevVelocity.x * dt,
							ydistanceMove));
					} else if (ydistanceMove == 0) {
						newVelocity = (sf::Vector2f(
							xdistanceMove,
							prevVelocity.y * dt));
					}

					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					sf::RectangleShape tempEntity1;
					tempEntity1.setSize(entity1.getSize());
					tempEntity1.setPosition(
						entity1.getPosition()
						+ newVelocity);
					bool stillCollide = checkCollision(
						tempEntity1, entity2,
						prevVelocity, dt);

					if (stillCollide) {

						std::cout
							<< "in prevVelocity ydirCol and xdirCol!!!!"
							<< std::endl;
						std::cout
							<< "in ydirCol and xdirCol!!!!"
							<< std::endl;

						std::cout
							<< "playerpos moving x direction: = "
							<< (playerPosition
							    + sf::Vector2f(
								      prevVelocity.x
									      * dt,
								      newVelocity
									      .y))
								   .x
							<< " "
							<< (playerPosition
							    + sf::Vector2f(
								      prevVelocity.x
									      * dt,
								      newVelocity
									      .y))
								   .y
							<< std::endl;

						std::cout
							<< "playerpos moving y direction: = "
							<< (playerPosition
							    + sf::Vector2f(
								      newVelocity
									      .x,
								      prevVelocity.y
									      * dt))
								   .x
							<< " "
							<< (playerPosition
							    + sf::Vector2f(
								      newVelocity
									      .x,
								      prevVelocity.y
									      * dt))
								   .y
							<< std::endl;

						sf::RectangleShape tempXentity1,
							tempYentity1;
						tempXentity1.setSize(
							entity1.getSize());
						tempYentity1.setSize(
							entity1.getSize());


						tempXentity1.setPosition(
							entity1.getPosition());
						tempYentity1.setPosition(
							entity1.getPosition());
						std::cout
							<< "first checkCollision = "
							<< !checkCollision(
								   tempXentity1,
								   entity2,
								   sf::Vector2f(
									   prevVelocity
										   .x,
									   newVelocity.y
										   / dt),
								   dt)
							<< ", second checkCollision = "
							<< !checkCollision(
								   tempYentity1,
								   entity2,
								   sf::Vector2f(
									   newVelocity.x
										   / dt,
									   prevVelocity
										   .y),
								   dt)
							<< std::endl;
						/*
						if
						(!checkCollision(tempXonlyEntity1,
								    entity2)) {
							newVelocity =
						sf::Vector2f( xdistanceMove, 0);
						} else if (!checkCollision(
								   tempYonlyEntity1,
								   entity2)) {
							newVelocity =
						sf::Vector2f( 0, ydistanceMove);
						}
					   */

						if (!checkCollision(
							    tempXentity1,
							    entity2,
							    sf::Vector2f(
								    prevVelocity
									    .x,
								    newVelocity.y
									    / dt),
							    dt)) { // check
								   // only
								   // move
								   // in x
								   // direction
							newVelocity = sf::Vector2f(
								prevVelocity.x
									* dt,
								newVelocity.y);
						} else if (
							!checkCollision(
								tempYentity1,
								entity2,
								sf::Vector2f(
									newVelocity.x
										/ dt,
									prevVelocity
										.y),
								dt)) { // check
							// only move
							// in y
							// direction
							newVelocity = sf::Vector2f(
								newVelocity.x,
								prevVelocity.y
									* dt);
						} else {
							/*
							newVelocity =
							sf::Vector2f(
								calculateEpsilon(
									entity1,
									entity2,
									prevVelocity
										.x,
									0),
								calculateEpsilon(
									entity1,
									entity2,
									prevVelocity
										.y,
									0));
							*/

							sf::Vector2f tempNewVelocity = sf::Vector2f(
								calculateEpsilon(
									entity1,
									entity2,
									prevVelocity
										.x,
									0),
								calculateEpsilon(
									entity1,
									entity2,
									prevVelocity
										.y,
									1));
							sf::RectangleShape
								tempPlayer;
							tempPlayer.setSize(
								entity1.getSize());
							tempEntity1.setPosition(
								playerPosition
								+ tempNewVelocity);

							if (checkBruteForceCollision(
								    tempPlayer,
								    entity2)) {


								newVelocity =
									tempNewVelocity;
							}


							/*
							if (playerPosition.x
									    +
							tempNewVelocity .x
								    <=
							playerPosition.x
									       + newVelocity
											 .x
							    && playerPosition.y
									       + newVelocity
											 .y
								       <=
							playerPosition.y
										  + newVelocity
											    .y) {
								newVelocity =
									tempNewVelocity;
							}
							*/
						}
					}
				} else { // both x and y direction are
					 // 0!!
					std::cout << "in prevVelocity both 0!!"
						  << std::endl;
					sf::RectangleShape tempXonlyEntity1,
						tempYonlyEntity1;
					tempXonlyEntity1.setSize(
						entity1.getSize());
					tempYonlyEntity1.setSize(
						entity1.getSize());

					tempXonlyEntity1.setPosition(
						entity1.getPosition());

					tempYonlyEntity1.setPosition(
						entity1.getPosition());
					std::cout
						<< "xonly checkCollision=   "
						<< !checkCollision(
							   tempXonlyEntity1,
							   entity2,
							   sf::Vector2f(
								   prevVelocity
									   .x,
								   0),
							   dt)

						<< "yonly checkCollision= "
						<< !checkCollision(
							   tempYonlyEntity1,
							   entity2,
							   sf::Vector2f(
								   0,
								   prevVelocity
									   .y),
							   dt)
						<< std::endl;

					if (!checkCollision(
						    tempXonlyEntity1, entity2,
						    sf::Vector2f(prevVelocity.x,
								 0),
						    dt)) {
						newVelocity = sf::Vector2f(
							0, prevVelocity.y);
					} else if (
						!checkCollision(
							tempYonlyEntity1,
							entity2,
							sf::Vector2f(
								0,
								prevVelocity.y
									* dt),
							dt)) {
						newVelocity = sf::Vector2f(
							prevVelocity.x * dt, 0);
					}
					/*
					else {
						newVelocity =
					sf::Vector2f(0, 0);
					}

					*/
				}
				/*
				else {
					newVelocity = sf::Vector2f(0,
				0);
				}

				*/

				std::cout << "player position after adding "
					  << (playerPosition + newVelocity).x
					  << " "
					  << (playerPosition + newVelocity).y
					  << std::endl;


				/*
				else {
					newVelocity =
						sf::Vector2f(0, 0);
				}
				*/
			}
			std::cout << "player position after adding "
				  << (playerPosition + newVelocity).x << " "
				  << (playerPosition + newVelocity).y
				  << std::endl;

			std::cout << "the new velocity  " << (newVelocity).x
				  << " " << (newVelocity).y << std::endl;
			std::cout << "player x size =" << entity1.getSize().x
				  << ", player y size = " << entity1.getSize().y
				  << std::endl;
			std::cout << "player position after adding "
				  << (playerPosition + newVelocity).x << " "
				  << (playerPosition + newVelocity).y
				  << std::endl;
			playerDeltaTime = 1;

		}

		else {
			/*
		// y increase downward, x incerase right
		int deltax, deltay;
		if ((entity2.getPosition().x <= entity1.getPosition().x)
		    && (entity2.getPosition().x + entity2.getSize().x
			>= entity1.getPosition().x
				   + entity1.getSize().x)) {
			deltax = 0;
		}
		// if player is to the left of wall
		else if ((entity1.getPosition().x + entity1.getSize().x
			  > entity2.getPosition().x)
			 && (entity1.getPosition().x
				     + entity1.getSize().x
			     < entity2.getPosition().x
				       + entity2.getSize().x)) {
			deltax = -1;
		}
		// if player is to the right of wall
		else {
			deltax = 1;
		}

		// for y axis

		if ((entity2.getPosition().y <= entity1.getPosition().y)
		    && (entity2.getPosition().y + entity2.getSize().y
			>= entity1.getPosition().y
				   + entity1.getSize().y)) {
			deltay = 0;
		}
		// if player is above the  wall
		else if ((entity1.getPosition().y + entity1.getSize().y
			  > entity2.getPosition().y)
			 && (entity1.getPosition().y
				     + entity1.getSize().y
			     < entity2.getPosition().y
				       + entity2.getSize().y)) {
			deltay = 1;

		}
		// if player is below the  wall
		else {
			deltay = -1;
		}


		// TODO THIS IS HARD CODED ;((((
		*/

			// wall walk before angle will not give y collide..
			/*
			bool xcollide =
				(entity1.getPosition().x + entity1.getSize().x
				 > entity2.sf::Shape::getPosition().x)
				&& (entity2.getPosition().x
					    + entity2.getSize().x
				    > entity1.sf::Shape::getPosition().x);
			bool ycollide =
				(entity1.getPosition().y + entity1.getSize().y
				 > entity2.sf::Shape::getPosition().y)
				&& (entity2.getPosition().y
					    + entity2.getSize().y
				    > entity1.sf::Shape::getPosition().y);
					*/
			std::cout << "in DIAGONAL!!" << std::endl;

			for (size_t i = 0; i < xcollidePoints.size(); ++i) {
				std::cout << " xcollide point " << i << " = "
					  << xcollidePoints[i].x << " "
					  << xcollidePoints[i].y << std::endl;
				;
			}
			for (size_t i = 0; i < ycollidePoints.size(); ++i) {
				std::cout << " ycollide point " << i << " = "
					  << ycollidePoints[i].x << " "
					  << ycollidePoints[i].y << std::endl;
				;
			}
			std::cout << "xdistanceMove = " << xdistanceMove
				  << std::endl;
			std::cout << "ydistanceMove = " << ydistanceMove
				  << std::endl;

			temp = std::min(std::abs(xdistanceMove),
					std::abs(ydistanceMove));
			// temp = std::min(xdistanceMove, ydistanceMove);
			// std::cin.get();

			if (temp == std::abs(xdistanceMove)) {
				std::cout << "temp go to XXX  " << std::endl;

				if (velocity != sf::Vector2f(0, 0)) {
					std::cout << "the new velocity  "
						  << (newVelocity).x << " "
						  << (newVelocity).y
						  << std::endl;
					std::cout << "player x size ="
						  << entity1.getSize().x
						  << ", player y size = "
						  << entity1.getSize().y
						  << std::endl;

					newVelocity =
						(sf::Vector2f(xdistanceMove,
							      velocity.y * dt));
					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;
					sf::RectangleShape tempEntity1 =
						sf::RectangleShape(
							entity1.getSize());
					tempEntity1.setSize(playerPosition
							    + newVelocity);

					bool ydirCol =
						(tempEntity1.getPosition().y
							 + tempEntity1.getSize()
								   .y
						 > entity2.getPosition().y)
						&& (entity2.getPosition().y
							    + entity2.getSize()
								      .y
						    > tempEntity1.getPosition()
							      .y);

					bool xdirCol =
						(tempEntity1.getPosition().x
							 + tempEntity1.getSize()
								   .x
						 > entity2.getPosition().x)
						&& (entity2.getPosition().x
							    + entity2.getSize()
								      .x
						    > tempEntity1.getPosition()
							      .x);

					if (ydirCol
					    && xdirCol) { // if still collide
							  // after
						// moving at x direction
						std::cout << " in yDirCol!!!!"
							  << std::endl;
						newVelocity = sf::Vector2f(
							xdistanceMove,
							ydistanceMove);
					}

					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;
					std::cout << "old velocity = "
						  << velocity.x << ", "
						  << velocity.y << std::endl;
					std::cout << "new  velocity = "
						  << newVelocity.x << ", "
						  << newVelocity.y << std::endl;
					playerDeltaTime = 1;
				} else {

					newVelocity = (sf::Vector2f(
						xdistanceMove,
						prevVelocity.y * dt));
					// newVelocity = (sf::Vector2f(
					// xdistanceMove,
					// prevVelocity.y * dt));
					playerDeltaTime = 1;
				}
				/*
				else {

					std::cout << "temp go to PREVVELOCITY  "
						  << std::endl;

					std::cout << "the new velocity  "
						  << (newVelocity).x << " "
						  << (newVelocity).y
						  << std::endl;
					std::cout << "player x size ="
						  << entity1.getSize().x
						  << ", player y size = "
						  << entity1.getSize().y
						  << std::endl;

					newVelocity = (sf::Vector2f(
						xdistanceMove,
						prevVelocity.y * dt));
					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding
				"
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;
					sf::RectangleShape tempEntity1 =
						sf::RectangleShape(
							entity1.getSize());
					tempEntity1.setSize(playerPosition
							    + newVelocity);

					bool ydirCol =
						(tempEntity1.getPosition().y
							 + tempEntity1.getSize()
								   .y
						 > entity2.getPosition().y)
						&& (entity2.getPosition().y
							    + entity2.getSize()
								      .y
						    > tempEntity1.getPosition()
							      .y);

					bool xdirCol =
						(tempEntity1.getPosition().x
							 + tempEntity1.getSize()
								   .x
						 > entity2.getPosition().x)
						&& (entity2.getPosition().x
							    + entity2.getSize()
								      .x
						    > tempEntity1.getPosition()
							      .x);

					if (ydirCol
					    && xdirCol) { // if still collide
							  // after
						// moving at x direction
						std::cout << " in yDirCol!!!!"
							  << std::endl;
						// newVelocity = sf::Vector2f(
						// prevVelocity.x * dt
						//+ xdistanceMove,
						// ydistanceMove);
					}

					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding
				"
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;
					std::cout << "old velocity = "
						  << velocity.x << ", "
						  << velocity.y << std::endl;
					std::cout << "new  velocity = "
						  << newVelocity.x << ", "
						  << newVelocity.y << std::endl;
					playerDeltaTime = 1;
					// newVelocity =
					// velocity
					//+ (sf::Vector2f(xdistanceMove,
					// 0))
					/// dt;
				}
			*/
			} else {

				std::cout << "temp go to YYY" << std::endl;

				if (velocity != sf::Vector2f(0, 0)) {
					std::cout << "the new velocity  "
						  << (newVelocity).x << " "
						  << (newVelocity).y
						  << std::endl;
					std::cout << "player x size ="
						  << entity1.getSize().x
						  << ", player y size = "
						  << entity1.getSize().y
						  << std::endl;
					newVelocity =
						(sf::Vector2f(velocity.x * dt,
							      ydistanceMove));
					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					sf::RectangleShape tempEntity1 =
						sf::RectangleShape(
							entity1.getSize());
					tempEntity1.setPosition(playerPosition
								+ newVelocity);

					bool ydirCol =
						(tempEntity1.getPosition().y
							 + tempEntity1.getSize()
								   .y
						 > entity2.getPosition().y)
						&& (entity2.getPosition().y
							    + entity2.getSize()
								      .y
						    > tempEntity1.getPosition()
							      .y);
					bool xdirCol =
						(tempEntity1.getPosition().x
							 + tempEntity1.getSize()
								   .x
						 > entity2.getPosition().x)
						&& (entity2.getPosition().x
							    + entity2.getSize()
								      .x
						    > tempEntity1.getPosition()
							      .x);
					if (xdirCol
					    && ydirCol) { // if still collide

						std::cout << " in xDirCol!!!!"
							  << std::endl;
						newVelocity = sf::Vector2f(
							xdistanceMove,
							ydistanceMove);
					}

					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					std::cout << "old velocity = "
						  << velocity.x << ", "
						  << velocity.y << std::endl;

					std::cout << "new  velocity = "
						  << newVelocity.x << ", "
						  << newVelocity.y << std::endl;
					playerDeltaTime = 1;
				}

				else {

					// CHANGE XXXXXXXXXXXX TODO
					newVelocity = (sf::Vector2f(
						prevVelocity.x * dt,
						ydistanceMove));
					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding "
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					std::cout << "old velocity = "
						  << velocity.x << ", "
						  << velocity.y << std::endl;

					std::cout << "new  velocity = "
						  << newVelocity.x << ", "
						  << newVelocity.y << std::endl;
					playerDeltaTime = 1;
				}
				/*
				else {

					std::cout << "temp go to PREVVELOCITY"
						  << std::endl;


					std::cout << "the new velocity  "
						  << (newVelocity).x << " "
						  << (newVelocity).y
						  << std::endl;
					std::cout << "player x size ="
						  << entity1.getSize().x
						  << ", player y size = "
						  << entity1.getSize().y
						  << std::endl;
					newVelocity = (sf::Vector2f(
						prevVelocity.x * dt,
						ydistanceMove));
					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding
				"
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					sf::RectangleShape tempEntity1 =
						sf::RectangleShape(
							entity1.getSize());
					tempEntity1.setPosition(playerPosition
								+ newVelocity);

					bool ydirCol =
						(tempEntity1.getPosition().y
							 + tempEntity1.getSize()
								   .y
						 > entity2.getPosition().y)
						&& (entity2.getPosition().y
							    + entity2.getSize()
								      .y
						    > tempEntity1.getPosition()
							      .y);
					bool xdirCol =
						(tempEntity1.getPosition().x
							 + tempEntity1.getSize()
								   .x
						 > entity2.getPosition().x)
						&& (entity2.getPosition().x
							    + entity2.getSize()
								      .x
						    > tempEntity1.getPosition()
							      .x);
					if (xdirCol
					    && ydirCol) { // if still collide

						std::cout << " in xDirCol!!!!"
							  << std::endl;
						std::cout
							<< "
				tempEntity1.getPosition().x"
							<< tempEntity1
								   .getPosition()
								   .x
							<< std::endl;

						std::cout
							<< "
				tempEntity1.getPosition().x+
				tempEntity1.getSize()"
							<<
				tempEntity1.getPosition() .x
								   + tempEntity1
									     .getSize()
									     .x
							<< std::endl;

						std::cout
							<< "
				entity2.getPosition().x"
							<< entity2.getPosition()
								   .x
							<< std::endl;
						std::cout
							<< "
				entity2.getPosition().x+ entity2.getSize().x"
							<< entity2.getPosition()
									   .x
								   +
				entity2.getSize() .x
							<< std::endl;


						// newVelocity = sf::Vector2f(
						// xdistanceMove,
						// prevVelocity.y * dt
						//+ ydistanceMove);
					}

					std::cout << "player position before "
						  << (playerPosition).x << " "
						  << (playerPosition).y
						  << std::endl;
					std::cout
						<< "player position after adding
				"
						<< (playerPosition
						    + newVelocity)
							   .x
						<< " "
						<< (playerPosition
						    + newVelocity)
							   .y
						<< std::endl;

					std::cout << "old velocity = "
						  << velocity.x << ", "
						  << velocity.y << std::endl;

					std::cout << "new  velocity = "
						  << newVelocity.x << ", "
						  << newVelocity.y << std::endl;
					playerDeltaTime = 1;
				}
				*/
				// newVelocity =
				// velocity
				//+ (sf::Vector2f(0,
				// ydistanceMove))
				/// dt;
			}
		}
		// std::cin.get();

		// return std::make_optional(sf::Vector2f(0, 0));
		playerDeltaTime = 1;
		std::cout << "--------------------------------------"
			  << std::endl;
		return std::make_optional(newVelocity);
	} else {
		return std::nullopt;
	}
}

/*
bool ydirCol = (tempEntity1.getPosition().y + tempEntity1.getSize().y
		> entity2.getPosition().y)
	       && (entity2.getPosition().y + entity2.getSize().y
		   > tempEntity1.getPosition().y);

bool xdirCol = (tempEntity1.getPosition().x + tempEntity1.getSize().x
		> entity2.getPosition().x)
	       && (entity2.getPosition().x + entity2.getSize().x
		   > tempEntity1.getPosition().x);
if (ydirCol && xdirCol) {
	newVelocity = sf::Vector2f(0, 0);
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


/*
std::optional<sf::Vector2f>
iow::checkAndResolveCollisionDelta(sf::RectangleShape entity1,
				   sf::RectangleShape entity2,
				   size_t pushFactor)
{


	// entity 2 is wall, and entity 1 is player!!!!!!
	// position start at top left corner, add 0.2f as the bounding
box bool xcollide = (entity1.getPosition().x + entity1.getSize().x >
entity2.sf::Shape::getPosition().x)
			&& (entity2.getPosition().x +
entity2.getSize().x > entity1.sf::Shape::getPosition().x); bool ycollide
= (entity1.getPosition().y + entity1.getSize().y >
entity2.sf::Shape::getPosition().y)
			&& (entity2.getPosition().y +
entity2.getSize().y > entity1.sf::Shape::getPosition().y); float deltax,
deltay; if (xcollide && ycollide == true) {

		// for x axis
		// if the player is inside the wall's boundary
		if ((entity2.getPosition().x <= entity1.getPosition().x)
		    && (entity2.getPosition().x + entity2.getSize().x
			>= entity1.getPosition().x +
entity1.getSize().x)) { deltax = 0;
		}
		// if player is to the left of wall
		else if ((entity1.getPosition().x + entity1.getSize().x
			  > entity2.getPosition().x)
			 && (entity1.getPosition().x +
entity1.getSize().x < entity2.getPosition().x + entity2.getSize().x)) {
			deltax = entity2.getPosition().x
				 - entity1.getPosition().x -
entity1.getSize().x
				 - pushFactor;
		}
		// if player is to the right of wall
		else {
			deltax = entity2.getPosition().x +
entity2.getSize().x
				 + pushFactor - entity1.getPosition().x;
		}

		// for y axis

		if ((entity2.getPosition().y <= entity1.getPosition().y)
		    && (entity2.getPosition().y + entity2.getSize().y
			>= entity1.getPosition().y +
entity1.getSize().y)) { deltay = 0;
		}
		// if player is above the  wall
		else if ((entity1.getPosition().y + entity1.getSize().y
			  > entity2.getPosition().y)
			 && (entity1.getPosition().y +
entity1.getSize().y < entity2.getPosition().y + entity2.getSize().y)) {
			deltay = entity2.getPosition().y
				 - entity1.getPosition().y -
entity1.getSize().y
				 - pushFactor;

		}
		// if player is below the  wall
		else {
			deltay = entity2.getPosition().y +
entity2.getSize().y
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
				std::min(std::abs(deltax),
std::abs(deltay)); if (temp == std::abs(deltax)) { tempv.x = deltax;
				tempv.y = 0;
			} else {
				tempv.y = deltay;
				tempv.x = 0;
			}
		}
		std::cout << "collision cocured" << std::endl;
		std::cout << "xcollide = " << xcollide << std::endl;
		std::cout << "entity1 xpos = " <<
entity1.getPosition().x
			  << std::endl;
		std::cout << "entity1 xpos+size = "
			  << entity1.getPositioCord [i]= " <<
playerCord[i].x
				  << " " << playerCord[i].y <<
std::endl;

			std::cout << "playerCord [i+1]= " <<
playerCord[i + 1].x
				  << " " << playerCord[i + 1].y <<
std::endl;

			std::cout << "wallCord [tempCounter]= "
				  << wallCord[tempCounter].x << " "
				  << wallCord[tempCounter].y <<
std::endl;

			std::cout << "wallCord [tempCounter+1]= "
				  << wallCord[tempCounter + 1].x << " "
				  << wallCord[tempCounter + 1].y <<
std::en().x
+ entity1.getSize().x
			  << std::endl;
		std::cout << "entity2 xpos = " <<
entity2.getPosition().x
			  << std::endl;
		std::cout << "entity2 xpos+size = "
			  << entity2.getPosition().x +
entity2.getSize().x
			  << std::endl;
		std::cout << "ycollide = " << ycollide << std::endl;
		std::cout << "entity1 ypos = " <<
entity1.getPosition().y
			  << std::endl;
		std::cout << "entity1 ypos+size = "
			  << entity1.getPosition().y +
entity1.getSize().y
			  << std::endl;
		std::cout << "entity2 ypos = " <<
entity2.getPosition().y
			  << std::endl;
		std::cout << "entity2 ypos+size = "
			  << entity2.getPosition().y +
entity2.getSize().y
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

