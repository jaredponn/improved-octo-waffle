#include <SFML/Graphics.hpp>
#include <iostream>

namespace iow
{

void mutateRectangle(sf::RectangleShape &rect, const sf::Vector2f size,
		     const sf::Vector2f pos, const sf::Color color);
void mutateCircle(sf::CircleShape &circle, const float radius,
		  const sf::Vector2f pos, const sf::Color color);

} // namespace iow
