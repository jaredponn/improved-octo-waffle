#include <SFML/Graphics.hpp>
#include <vector>

#include "input.h"
#include "ecs.h"
#include "graphics.h"
#include "packedvector.h"

constexpr unsigned int MAX_ENTITIES = 1000000;

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "waffle",
				sf::Style::Close);
	iow::InputManager::initInputManager();
	iow::ECS ecs(MAX_ENTITIES);

	sf::Clock clock;
	sf::Time ti = sf::microseconds(0);
	sf::Time tf = sf::microseconds(0);
	sf::Time dt = sf::microseconds(0);

	while (window.isOpen()) {
		ti = clock.getElapsedTime();
		iow::InputManager::shiftAndUpdateInputbuffer();

		ecs.runECS(dt, iow::InputManager::getKeyBuffer());


		tf = clock.getElapsedTime();
		dt = tf = ti;
	}

	return 0;
}
