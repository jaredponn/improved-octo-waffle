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
#define X_CPT(name, type)                                                      \
	MK_COMPONENT_MEMBER_VAR_NAME(name).delete_element_at_sparse_vector(    \
		index);

	IOW_COMPONENT_LIST
#undef X_CPT

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
	enemyTmp = create_new_entity();
	c_IsEnemy.add_element_at_sparse_vector(enemyTmp, true);
	c_Speed.add_element_at_sparse_vector(enemyTmp, sf::Vector2f{0, 0});
	c_Position.add_element_at_sparse_vector(
		enemyTmp, resourceManager.m_enemy_config.spawnPosition);
	c_HP.add_element_at_sparse_vector(enemyTmp,
					  resourceManager.m_enemy_config.hp);
	c_Appearance.add_element_at_sparse_vector(
		enemyTmp, resourceManager.m_enemy_config.sprite);
	c_SteeringBehav.add_element_at_sparse_vector(
		enemyTmp, resourceManager.m_enemy_config.steeringBehaviour);

	/* spawning the world */
	for (size_t i = 0;
	     i < resourceManager.m_tile_map_config.getTileMapSize(); ++i) {
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

	/*  parsing game keys */
	iow::parseGameKeys(*this, resourceManager);

	/* Systems... */
	window.clear(); // clears the color for the buffer

	c_DeltaTime[m_player_entity] = dt;

	iow::checkAndResolveCollisionOfPlayerAgainstWall(
		c_PlayerCollisionLayer[m_player_entity],
		c_Speed[m_player_entity], c_PrevSpeed[m_player_entity], dt,
		c_DeltaTime[m_player_entity], c_TileCollisionLayer);

	c_PrevSpeed[m_player_entity] = c_Speed[m_player_entity] / dt;

	iow::updateVelocityToSeek(c_Speed, c_IsEnemy, c_Position,
				  c_SteeringBehav, c_Position[m_player_entity]);

	iow::updateVelocityToFlee(c_Speed, c_IsEnemy, c_Position,
				  c_SteeringBehav);

	iow::updatePositionFromSpeed(dt, c_Position, c_Speed);

	iow::updateCollisionBoxFromPosition(c_PlayerCollisionLayer, c_Position);

	// iow::updateEnemyBoxPosFromPosition(c_IsEnemy, c_EnemyColBox,
	//				   c_Position);
	// iow::updateCirclePosFromPosition(c_IsBullet, c_BulletCircle,
	//				 c_Position);


	iow::updateCamera(m_camera, c_Position[m_player_entity],
			  window.getSize());
	iow::updateAppearanceFromPosition(c_Appearance, c_Position);

	/*HAIYANG::: c_IsBullet -> the bool packed vector for determing which
	 * indicies are a bullet*/

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

	/* internal game logic*/
	iow::parseInternalGameEvents(*this, m_internal_game_event_stack);
}

} // namespace iow
