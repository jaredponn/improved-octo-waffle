#include <SFML/Graphics.hpp>
#include <iostream>

#include "camera.h"

namespace iow
{

// takes in the size, xcord, ycord, and color of the
// rectangle
extern void mutateRectangle(sf::RectangleShape &rect, const sf::Vector2f size,
			    const sf::Vector2f pos, const sf::Color color);

// takes in the size, xcord, ycord, and color of the
// rectangle
extern void mutateCircle(sf::CircleShape &circle, const float radius,
			 const sf::Vector2f pos, const sf::Color color);

} // namespace iow
