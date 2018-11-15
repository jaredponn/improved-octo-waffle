#include "ecs.h"
#include "systems.h"
#include "logger.h"
#include <iostream>

namespace iow
{
iow::ECS::ECS(size_t capacity) : Components(capacity), ExtraState()
{

	for (size_t i = 0; i < capacity; ++i) {
		m_free_indices.push(i);
	}
	// TODO initailize the empty state
}

size_t iow::ECS::create_new_entity()
{
	size_t tmp = m_free_indices.top();
	m_free_indices.pop();
	return tmp;
}

// TODO the delete_entity_at() function
size_t iow::ECS::delete_entity_at(size_t index)
{
	// TODO
	Logger::logMessage(
		"ERROR deleting entity. This has not been implemented yet.");
	(void)index;
	return 0;
}

void iow::ECS::initECS(sf::RenderWindow &window,
		       iow::ResourceManager &resourceManager)
{
	// creating the player entity
	size_t playerEntity = create_new_entity();
	c_IsPlayer.add_element_at_sparse_vector(playerEntity, true);
	c_Speed.add_element_at_sparse_vector(
		playerEntity, resourceManager.m_player_config.speed);
	c_Position.add_element_at_sparse_vector(
		playerEntity, resourceManager.m_player_config.position);
	c_HP.add_element_at_sparse_vector(playerEntity,
					  resourceManager.m_player_config.hp);
	c_Appearance.add_element_at_sparse_vector(
		playerEntity, resourceManager.m_player_config.sprite);

	// spawning the world TODO
}

void iow::ECS::runECS(float dt, sf::RenderWindow &window,
		      iow::ResourceManager &resourceManager)
{

	// game logic
	runGameLogic(dt, resourceManager);


	// Systems...
	iow::updateAppearanceFromPosition(c_Appearance, c_Position);
	iow::renderSystem(c_Appearance, window, m_camera);

	// Push output to the screen
	window.display();
}

void iow::ECS::runGameLogic(float dt, iow::ResourceManager &resourceManager)
{
	size_t playerEntity = c_IsPlayer.get_global_index_from_packed_index(0);
	for (size_t i = 0; i < iow::MAX_NUMBER_KEYS; ++i) {

		if (iow::InputManager::getKeyState(
			    static_cast<sf::Keyboard::Key>(i))
		    == std::get<0>(resourceManager.m_key_binds[i])) {
			switch (std::get<1>(resourceManager.m_key_binds[i])) {

			case iow::PlayerGameEvents::MOVE_PLAYER_DOWN:
				c_Position[playerEntity] += sf::Vector2f(1, 1);
				break;
			case iow::PlayerGameEvents::MOVE_PLAYER_UP:
				break;
			case iow::PlayerGameEvents::MOVE_PLAYER_LEFT:
				break;
			case iow::PlayerGameEvents::MOVE_PLAYER_RIGHT:
				break;

			default:
				break;
			}
		}
	}
}

} // namespace iow
