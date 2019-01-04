#include "ecs.h"
#include "logger.h"
#include "parsegamekeys.h"
#include "parseinternalgameevents.h"
#include "systems.h"
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

/* HAIYANG use this to remove a bullet entity from the engine */
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
	c_IsPlayer.add_element_at_sparse_vector(m_player_entity, true);

	c_Position.add_element_at_sparse_vector(
		m_player_entity, resourceManager.m_player_config.spawnPosition);
	c_Speed.add_element_at_sparse_vector(m_player_entity,
					     sf::Vector2f(0, 0));
	c_PrevSpeed.add_element_at_sparse_vector(m_player_entity,
						 sf::Vector2f(0, 0));
	c_HP.add_element_at_sparse_vector(m_player_entity,
					  resourceManager.m_player_config.hp);
	c_Appearance.add_element_at_sparse_vector(
		m_player_entity, resourceManager.m_player_config.sprite);
	c_Direction.add_element_at_sparse_vector(m_player_entity,
						 iow::Directions::UP);
	c_PlayerCollisionLayer.add_element_at_sparse_vector(
		m_player_entity, resourceManager.m_player_config.collisionBox);
	// TODO
	c_DeltaTime.add_element_at_sparse_vector(m_player_entity, 0);

	/* intializing the camera */
	m_camera.position = resourceManager.m_camera_config.position;
	m_camera.scale = resourceManager.m_camera_config.scale;

	/* spawning enemies */
	size_t enemyTmp;
	for (size_t i = 0; i < 1; ++i) {
		enemyTmp = create_new_entity();
		c_IsEnemy.add_element_at_sparse_vector(enemyTmp, true);
		c_Speed.add_element_at_sparse_vector(enemyTmp,
						     sf::Vector2f{0, 0});
		c_Position.add_element_at_sparse_vector(
			enemyTmp, resourceManager.m_enemy_config.spawnPosition
					  * (float)i);
		iow::CollisionBox tempColBox =
			resourceManager.m_enemy_config.enemyColBox;
		tempColBox.setPosition(
			resourceManager.m_enemy_config.spawnPosition
			* (float)i);
		c_EnemyColBox.add_element_at_sparse_vector(enemyTmp,
							   tempColBox);
		c_HP.add_element_at_sparse_vector(
			enemyTmp, resourceManager.m_enemy_config.hp);
		c_Appearance.add_element_at_sparse_vector(
			enemyTmp, resourceManager.m_enemy_config.sprite);
		c_SteeringBehav.add_element_at_sparse_vector(
			enemyTmp,
			resourceManager.m_enemy_config.steeringBehaviour);
	}

	/* spawning the world */
	std::cout << " tile map size "
		  << resourceManager.m_tile_map_config.getTileMapSize()
		  << std::endl;
	for (size_t i = 0;
	     // i < resourceManager.m_tile_map_config.getTileMapSize(); ++i) {
	     i < 100; ++i) {
		size_t tileEntity = create_new_entity();
		const auto &tmp = resourceManager.m_tile_map_config.getTile(i);
		const auto &tileWorldPosition = std::get<0>(tmp);
		const auto &tileType = std::get<1>(tmp);
		const auto &tileConf =
			resourceManager.m_tile_map_config.getTileConfig(
				tileType);

		c_TilePosition.add_element_at_sparse_vector(tileEntity,
							    tileWorldPosition);

		c_TileAppearance.add_element_at_sparse_vector(tileEntity,
							      tileConf.sprite);

		// TODO actually make the collisions work. Make a player
		// collision comppnent and a system that will use a la haiyang
		// he's system to check if colliusion work
		if (tileConf.collision) {
			c_TileCollisionLayer.add_element_at_sparse_vector(
				tileEntity,
				iow::setCollisionBoxPositionFromPosition(
					tileConf.collision.value(),
					tileWorldPosition));
		}
	}

	iow::updateAppearanceFromPosition(c_TileAppearance, c_TilePosition);
}

void iow::ECS::runECS(float dt, sf::RenderWindow &window,
		      iow::ResourceManager &resourceManager)
{

	/*  game logic */
	runGameLogic(resourceManager);

	/* Systems... */
	window.clear(); // clears the color for the buffer
	// sf::Vector2f tempPrevSpeed = c_Speed[m_player_entity];
	// get the delta time of the player
	c_DeltaTime[m_player_entity] = dt;

	iow::checkAndResolveCollisionOfPlayerAgainstWall(
		c_PlayerCollisionLayer[m_player_entity],
		c_Speed[m_player_entity], c_PrevSpeed[m_player_entity], dt,
		c_DeltaTime[m_player_entity], c_TileCollisionLayer);
	// assigning the previous speed
	// std::cout << "old player position " << c_Position[m_player_entity].x
	//<< " " << c_Position[m_player_entity].y << std::endl;
	c_PrevSpeed[m_player_entity] = c_Speed[m_player_entity] / dt;
	// std::cout << " c_PrevSpeed[player] = " <<
	// c_PrevSpeed[m_player_entity].x
	//<< std::endl;
	// TODO
	iow::updatePositionFromSpeed(dt, c_Position, c_Speed, m_player_entity,
				     c_DeltaTime[m_player_entity]);

	iow::updateVelocityToSeek(c_Speed, c_IsEnemy, c_Position,
				  c_SteeringBehav, c_Position[m_player_entity]);

	iow::updateVelocityToFlee(c_Speed, c_IsEnemy, c_Position,
				  c_SteeringBehav);
	// std::cout << "player's new velocity in ecs.cpp: "
	//<< c_Speed[m_player_entity].x << " "
	//<< c_Speed[m_player_entity].y << std::endl;

	iow::updateCollisionBoxFromPosition(c_PlayerCollisionLayer, c_Position);
	iow::updateEnemyBoxPosFromPosition(c_IsEnemy, c_EnemyColBox,
					   c_Position);
	iow::updateCirclePosFromPosition(c_IsBullet, c_BulletCircle,
					 c_Position);


	iow::updateCamera(m_camera, c_Position[m_player_entity],
			  window.getSize());
	iow::updateAppearanceFromPosition(c_Appearance, c_Position);

	// iow::checkAndResolveCollisionBulletAgainstWallsAndZombies(
	// c_IsBullet, c_BulletCircle, c_BulletDamage, c_IsEnemy,
	// c_EnemyColBox, c_HP, c_TileCollisionLayer,
	// m_internal_game_event_stack);
	// iow::debugEnemyHP(c_HP);

	iow::renderSystem(c_TileAppearance, window, m_camera);
	iow::renderSystem(c_Appearance, window, m_camera);
	// debug render system for collision boxes
	// iow::debugRenderSystem(c_TileCollisionLayer, window, m_camera);
	// iow::debugRenderSystem(c_PlayerCollisionLayer, window, m_camera);


	/* Push output to the screen */
	window.display();
}

void iow::ECS::runGameLogic(iow::ResourceManager &resourceManager)
{
	iow::parseGameKeys(*this, resourceManager);
}

} // namespace iow
