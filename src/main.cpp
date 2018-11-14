#include <iostream>
#include <vector>
#include "packedvector.h"
<<<<<<< HEAD
#include "graphics.h"
#include <SFML/Graphics.hpp>
#include "input.h"
	int main(void)
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "waffle",
				sf::Style::Close);

	iow::InputManager::initInputManager();
	iow::PackedVector<int> a(121);
	a.add_element_at_sparse_vector(1, 23);
	a.delete_element_at_sparse_vector(1);
	// my bad graphics example:
	sf::RectangleShape rect1;
	// create the Vector2 vectors for the size, position, and color of the
	// shape
	sf::Vector2f sizeOfRect(40, 60);
	sf::Vector2f posOfRect(10, 20);
	sf::Color colorOfRect(100, 200, 250);
	// call the mutateRectangle in graphics.h to change the rectangle's size
	// and stuff.. can reuse to update its position
	iow::mutateRectangle(rect1, sizeOfRect, posOfRect, colorOfRect);

	// same thing here for the circle ;)
	sf::CircleShape cir1;
	float sizeOfCir = 80;
	sf::Vector2f posOfCir(400, 50);
	sf::Color colorOfCir(100, 200, 250);
	iow::mutateCircle(cir1, sizeOfCir, posOfCir, colorOfCir);
	// main game loop
	// displaying them
	while (1) {
		iow::inputmanager::shiftandupdateinputbuffer();
		window.draw(rect1);
		window.display();
		window.draw(cir1);
		window.display();
	}

	return 0;
}
