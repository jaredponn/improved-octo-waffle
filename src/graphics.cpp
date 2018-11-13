#include <SFML/Graphics.hpp>
#include <iostream>
#include "graphics.h"

void iow::mutateRectangle(sf::RectangleShape &rect, const sf::Vector2f size,
			  const sf::Vector2f pos, const sf::Color color)
{ // constructor that takes in the size, xcord, ycord, and color of the
  // rectangle
	rect.setSize(size);
	rect.setOrigin(pos.x / 2, pos.y / 2);
	rect.setPosition(pos);
	rect.setFillColor(color);
}

void iow::mutateCircle(sf::CircleShape &circle, const float radius,
		       const sf::Vector2f pos, const sf::Color color)
{ // constructor that takes in the size, xcord, ycord, and color of the
  // rectangle
	circle.setRadius(radius);
	circle.setOrigin(pos.x / 2, pos.y / 2);
	circle.setPosition(pos);
	circle.setFillColor(color);
}
