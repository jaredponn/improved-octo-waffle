#include "parseinternalgameevents.h"

namespace iow
{


void parseInternalGameEvents(iow::ECS &ecs,
			     std::stack<iow::InternalGameEvent> &gameEvents)
{
	while (!gameEvents.empty()) {
		iow::InternalGameEvent const tmp = gameEvents.top();
		gameEvents.pop();

		switch (tmp.type) {
		case InternalGameEventType::DELETE_BULLET:
			ecs.delete_entity_at(tmp.deleteBullet.bulletEntity);
			break;

		case InternalGameEventType::DELETE_ENEMY:
			ecs.delete_entity_at(tmp.deleteEnemy.enemyEntity);
			break;

		case InternalGameEventType::PLAYER_KNOCKBACK:
			ecs.c_Speed[tmp.playerKnockback.playerIndex] =
				sf::Vector2f(0, 0);
			break;
		}
	}
}

} // namespace iow
