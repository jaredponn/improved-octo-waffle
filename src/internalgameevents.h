#pragma once

#include <stack>

namespace iow
{

struct DeleteBullet {
	size_t bulletEntity;
};

struct DeleteEnemy {
	size_t enemyEntity;
};
struct PlayerKnockback {
	size_t playerIndex;
};

// Sum type of interanl game events
enum class InternalGameEventType {
	DELETE_BULLET,
	DELETE_ENEMY,
	PLAYER_KNOCKBACK
};
struct InternalGameEvent {
	iow::InternalGameEventType type;
	union {
		DeleteBullet deleteBullet;
		DeleteEnemy deleteEnemy;
		PlayerKnockback playerKnockback;
	};
};
} // namespace iow
