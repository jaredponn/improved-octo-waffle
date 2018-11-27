#include "gameinput.h"


namespace iow
{

/*

static inline void parseSingleKey(iow::ECS &ecs, const float dt,
			  const iow::ResourceManager &resourceManager)
{
//        for (size_t i = 0; i < iow::MAX_NUMBER_KEYS; ++i) {
//		if (iow::InputManager::getKeyState(
//			    static_cast<sf::Keyboard::Key>(i))
//		    == std::get<0>(resourceManager.m_key_binds[i])) {
//			switch (std::get<1>(resourceManager.m_key_binds[i]))
//{
//
//			case iow::PlayerGameEvents::MOVE_PLAYER_DOWN:
//				ecs.c_Position[m_player_entity] +=
//					dt
//					* sf::Vector2f(0,
//						       -resourceManager
//								.m_player_config
//								.speed.y);
//				break;
//			case iow::PlayerGameEvents::MOVE_PLAYER_UP:
//				ecs.c_Position[m_player_entity] +=
//					dt
//					* sf::Vector2f(0,
//						       resourceManager
//							       .m_player_config
//							       .speed.y);
//				break;
//			case iow::PlayerGameEvents::MOVE_PLAYER_LEFT:
//				ecs.c_Position[m_player_entity] +=
//					dt
//					* sf::Vector2f(-resourceManager
//								.m_player_config
//								.speed.x,
//						       0);
//				break;
//			case iow::PlayerGameEvents::MOVE_PLAYER_RIGHT:
//				ecs.c_Position[m_player_entity] +=
//					dt
//					* sf::Vector2f(resourceManager
//							       .m_player_config
//							       .speed.x,
//						       0);
//				break;
//
//			case iow::PlayerGameEvents::PLAYER_SHOOT: {
//				size_t bulletEntity =
//create_new_entity();
ecs.c_IsBullet.add_element_at_sparse_vector(
//					bulletEntity, true);
//				ecs.c_Position.add_element_at_sparse_vector(
//					bulletEntity,
//					c_Position[m_player_entity]);
//				ecs.c_Speed.add_element_at_sparse_vector(
//					bulletEntity,
//sf::Vector2f(2.f, 2.f));
//				ecs.c_Appearance.add_element_at_sparse_vector(
//					bulletEntity,
//					resourceManager.m_bullet_config.sprite);
//				break;
//			}
//
//			case iow::PlayerGameEvents::NO_ACTION:
//				break;
//			}
//		}
//	}
}

static inline void parseKeyChords(iow::ECS &ecs, const float dt,
			  const iow::ResourceManager &resourcemanager)
{
}

void parseKeyInputs(iow::ECS &ecs, const float dt,
	    const iow::ResourceManager &resourcemanager)
{
}
*/
} // namespace iow
