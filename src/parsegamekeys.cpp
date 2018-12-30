#include <iostream>

#include "directions.h"
#include "parsegamekeys.h"

namespace iow
{


static inline void parseGameInputs(iow::ECS &ecs, const float dt,
				   const iow::ResourceManager &resourceManager,
				   iow::PlayerGameEvents const event)

{
	switch (event) {
		/* player movement events */
	case iow::PlayerGameEvents::MOVE_PLAYER_DOWN:
		ecs.c_Direction[ecs.m_player_entity] = iow::Direction::DOWN;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_UP:
		ecs.c_Direction[ecs.m_player_entity] = iow::Direction::UP;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_LEFT:
		ecs.c_Direction[ecs.m_player_entity] = iow::Direction::LEFT;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_RIGHT:
		ecs.c_Direction[ecs.m_player_entity] = iow::Direction::RIGHT;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_UP_LEFT:
		ecs.c_Direction[ecs.m_player_entity] = iow::Direction::UP_LEFT;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_UP_RIGHT:
		ecs.c_Direction[ecs.m_player_entity] = iow::Direction::UP_RIGHT;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_DOWN_LEFT:
		ecs.c_Direction[ecs.m_player_entity] =
			iow::Direction::DOWN_LEFT;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;
	case iow::PlayerGameEvents::MOVE_PLAYER_DOWN_RIGHT:
		ecs.c_Direction[ecs.m_player_entity] =
			iow::Direction::DOWN_RIGHT;
		ecs.c_Position[ecs.m_player_entity] +=
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[ecs.m_player_entity])
			* resourceManager.m_player_config.speed * dt;
		break;


		/* player shoot event */
	case iow::PlayerGameEvents::PLAYER_SHOOT: {
		size_t bulletEntity = ecs.create_new_entity();
		ecs.c_IsBullet.add_element_at_sparse_vector(bulletEntity, true);
		ecs.c_Position.add_element_at_sparse_vector(
			bulletEntity, ecs.c_Position[ecs.m_player_entity]);
		ecs.c_BulletDamage.add_element_at_sparse_vector(bulletEntity,
								20);

		iow::CollisionCir tempCir =
			resourceManager.m_bullet_config.collisionCir;
		tempCir.setPosition(ecs.c_Position[ecs.m_player_entity]);
		ecs.c_BulletCircle.add_element_at_sparse_vector(bulletEntity,
								tempCir);
		ecs.c_Direction.add_element_at_sparse_vector(
			bulletEntity, ecs.c_Direction[ecs.m_player_entity]);
		ecs.c_Speed.add_element_at_sparse_vector(
			bulletEntity,
			iow::convertDirectionToNormalizedVector(
				ecs.c_Direction[bulletEntity])
				* resourceManager.m_bullet_config.speed);
		ecs.c_Appearance.add_element_at_sparse_vector(
			bulletEntity, resourceManager.m_bullet_config.sprite);
		break;
	}


	case iow::PlayerGameEvents::NO_ACTION:
		break;
	}
}

static inline void parseSingleKey(iow::ECS &ecs, const float dt,
				  const iow::ResourceManager &resourceManager)
{
	for (size_t i = 0; i < iow::MAX_NUMBER_KEYS; ++i) {
		if (iow::InputManager::getKeyState(
			    static_cast<sf::Keyboard::Key>(i))
		    == std::get<0>(resourceManager.m_key_binds[i])) {
			parseGameInputs(
				ecs, dt, resourceManager,
				std::get<1>(resourceManager.m_key_binds[i]));
		}
	}
}

static inline void parseKeyChords(iow::ECS &ecs, const float dt,
				  const iow::ResourceManager &resourceManager)
{
	for (const auto &i : resourceManager.m_key_chords) {

		bool tmp = true;

		// testing if all the have the right key state
		for (const auto &j : std::get<0>(i)) {
			tmp = iow::InputManager::getKeyState(std::get<0>(j))
				      == std::get<1>(j)
			      and tmp;
		}

		if (tmp) {
			parseGameInputs(ecs, dt, resourceManager,
					std::get<1>(i));

			// reseeting all the keys that were pressed to release,
			// so that game events with single key chords are not
			// double applied with the key chord
			for (const auto &j : std::get<0>(i)) {
				iow::InputManager::setKeyState(
					std::get<0>(j),
					iow::KeyState::RELEASED);
			}
		}
	}
}

void parseGameKeys(iow::ECS &ecs, float const dt,
		   iow::ResourceManager const &resourceManager)
{
	parseKeyChords(ecs, dt, resourceManager);
	parseSingleKey(ecs, dt, resourceManager);
}
} // namespace iow
