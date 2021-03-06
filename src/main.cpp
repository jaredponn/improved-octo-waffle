#include <SFML/Graphics.hpp>
#include <vector>

#include "collision.h"
#include "ecs.h"
#include "graphics.h"
#include "input.h"
#include "internalgameevents.h"
#include "packedvector.h"
#include "resourcemanager.h"

constexpr unsigned int MAX_ENTITIES = 1000000;

int main(void)
{

	iow::InputManager::initInputManager();
	iow::ResourceManager resourceManager;
	sf::RenderWindow window(sf::VideoMode(1080, 800), "waffle",
				sf::Style::Close);

	iow::ECS ecs(MAX_ENTITIES);
	ecs.initECS(window, resourceManager);

	sf::Clock clock;
	sf::Time ti = sf::microseconds(0);
	sf::Time tf = sf::microseconds(0);
	sf::Time dt = sf::microseconds(0);


	while (window.isOpen()) {
		ti = clock.getElapsedTime();

		iow::InputManager::shiftAndUpdateInputbuffer();
		ecs.runECS(dt.asMilliseconds(), window, resourceManager);

		tf = clock.getElapsedTime();

		dt = tf - ti;
	}

	return 0;
}
