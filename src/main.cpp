#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
#include <ratio>
#include <vector>

#include "collision.h"
#include "ecs.h"
#include "graphics.h"
#include "input.h"
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
	/*
	sf::Clock clock;
	sf::Time ti = sf::microseconds(0);
	sf::Time tf = sf::microseconds(0);
	sf::Time dt = sf::microseconds(0);
	*/
	std::chrono::high_resolution_clock::time_point
		ti = std::chrono::high_resolution_clock::now(),
		tf = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> dt =
		std::chrono::duration_cast<std::chrono::duration<float>>(tf
									 - ti);

	while (window.isOpen()) {
		ti = std::chrono::high_resolution_clock::now();

		iow::InputManager::shiftAndUpdateInputbuffer();
		ecs.runECS(dt.count(), window, resourceManager);

		tf = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration_cast<std::chrono::duration<double>>(
			tf - ti);
	}

	return 0;
}
