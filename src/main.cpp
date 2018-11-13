#include <iostream>
#include <vector>
#include "packedvector.h"
#include "input.h"


int main(void)
{
	iow::InputManager::initInputManager();
	sf::RenderWindow window(sf::VideoMode(600, 400), "window");

	// main game loop
	while (1) {
		iow::InputManager::shiftAndUpdateInputbuffer();
	};


	return 0;
}
