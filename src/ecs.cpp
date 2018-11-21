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
	Logger::logMessage("UNTESTED AND PROBABLY NOT WORKIGN");
#define X_CPT(name, type)                                                      \
	MK_COMPONENT_MEMBER_VAR_NAME(name).delete_element_at_sparse_vector(    \
		index);                                                        \
	IOW_COMPONENT_LIST
#undef X_CPT

	(void)index;
	return 0;
}

void iow::ECS::initECS(sf::RenderWindow &window,
		       iow::ResourceManager &resourceManager)
{
	(void)window;
	/* creating the player entity */
	m_player_entity = create_new_entity();

	/* c_Speed.add_element_at_sparse_vector( */
	/* 	m_player_entity, resourceManager.m_player_config.speed); */
	c_Position.add_element_at_sparse_vector(
		m_player_entity, resourceManager.m_player_config.spawnPosition);
	c_HP.add_element_at_sparse_vector(m_player_entity,
					  resourceManager.m_player_config.hp);
	c_Appearance.add_element_at_sparse_vector(
		m_player_entity, resourceManager.m_player_config.sprite);


	/* intializing the camera */
	m_camera.position = resourceManager.m_camera_config.position;
	m_camera.scale = resourceManager.m_camera_config.scale;

	/* spawning 5 enemies */
	size_t enemyTmp;
	for (size_t i = 0; i < 5; ++i) {
		enemyTmp = create_new_entity();
		/* c_Speed.add_element_at_sparse_vector( */
		/* 	enemyTmp, resourceManager.m_enemy_config.speed); */
		c_Position.add_element_at_sparse_vector(
			enemyTmp, resourceManager.m_enemy_config.spawnPosition);
		c_HP.add_element_at_sparse_vector(
			enemyTmp, resourceManager.m_enemy_config.hp);
		c_Appearance.add_element_at_sparse_vector(
			enemyTmp, resourceManager.m_enemy_config.sprite);
	}

	/* spawning the world */
	for (size_t i = 0;
	     i < resourceManager.m_tile_map_config.getTileMapSize(); ++i) {
		size_t tileEntity = create_new_entity();
		const auto &tmp = resourceManager.m_tile_map_config.getTile(i);

		c_TilePosition.add_element_at_sparse_vector(tileEntity,
							    std::get<0>(tmp));

		c_TileAppearance.add_element_at_sparse_vector(
			tileEntity, resourceManager.m_tile_map_config
					    .getTileConfig(std::get<1>(tmp))
					    .sprite);
	}

	iow::updateAppearanceFromPosition(c_TileAppearance, c_TilePosition);
}

void iow::ECS::runECS(float dt, sf::RenderWindow &window,
		      iow::ResourceManager &resourceManager)
{

	/*  game logic */
	runGameLogic(dt, resourceManager);

	/* Systems... */
	window.clear(); // clears the color for the buffer
	iow::updatePositionFromSpeed(dt, c_Position, c_Speed);
	iow::updateCamera(m_camera, c_Position[m_player_entity],
			  window.getSize());
	iow::updateAppearanceFromPosition(c_Appearance, c_Position);

	iow::renderSystem(c_TileAppearance, window, m_camera);
	iow::renderSystem(c_Appearance, window, m_camera);

	/* Push output to the screen */
	window.display();
}

void iow::ECS::runGameLogic(float dt, iow::ResourceManager &resourceManager)
{
	for (size_t i = 0; i < iow::MAX_NUMBER_KEYS; ++i) {
		if (iow::InputManager::getKeyState(
			    static_cast<sf::Keyboard::Key>(i))
		    == std::get<0>(resourceManager.m_key_binds[i])) {
			switch (std::get<1>(resourceManager.m_key_binds[i])) {

			case iow::PlayerGameEvents::MOVE_PLAYER_DOWN:
				c_Position[m_player_entity] +=
					dt
					* sf::Vector2f(0,
						       -resourceManager
								.m_player_config
								.speed.y);
				break;
			case iow::PlayerGameEvents::MOVE_PLAYER_UP:
				c_Position[m_player_entity] +=
					dt
					* sf::Vector2f(0,
						       resourceManager
							       .m_player_config
							       .speed.y);
				break;
			case iow::PlayerGameEvents::MOVE_PLAYER_LEFT:
				c_Position[m_player_entity] +=
					dt
					* sf::Vector2f(-resourceManager
								.m_player_config
								.speed.x,
						       0);
				break;
			case iow::PlayerGameEvents::MOVE_PLAYER_RIGHT:
				c_Position[m_player_entity] +=
					dt
					* sf::Vector2f(resourceManager
							       .m_player_config
							       .speed.x,
						       0);
				break;

			case iow::PlayerGameEvents::PLAYER_SHOOT: {
				size_t bulletEntity = create_new_entity();
				c_IsBullet.add_element_at_sparse_vector(
					bulletEntity, true);
				c_Position.add_element_at_sparse_vector(
					bulletEntity,
					c_Position[m_player_entity]);
				c_Speed.add_element_at_sparse_vector(
					bulletEntity, sf::Vector2f(2.f, 2.f));
				c_Appearance.add_element_at_sparse_vector(
					bulletEntity,
					resourceManager.m_bullet_config.sprite);
				break;
			}

			case iow::PlayerGameEvents::NO_ACTION:
				break;
			}
		}
	}
}

} // namespace iow
