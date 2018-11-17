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

// checks collision between 2 rectangles
std::optional<sf::Vector2f> checkCollision(sf::RectangleShape entity1,
					   sf::RectangleShape entity2);

// checks collision between a circle and a rectangle
bool checkCollision(sf::CircleShape entity1, sf::RectangleShape entity2);
} // namespace iow
