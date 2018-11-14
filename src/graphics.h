#include <SFML/Graphics.hpp>
#include <iostream>

namespace iow
{

void pushToRenderBuffer();


// takes in the size, xcord, ycord, and color of the
// rectangle
void mutateRectangle(sf::RectangleShape &rect, const sf::Vector2f size,
		     const sf::Vector2f pos, const sf::Color color);

// takes in the size, xcord, ycord, and color of the
// rectangle
void mutateCircle(sf::CircleShape &circle, const float radius,
		  const sf::Vector2f pos, const sf::Color color);


} // namespace iow
