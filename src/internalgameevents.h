#pragma once

#include <stack>

namespace iow
{

struct DeleteBullet {
	size_t bulletEntity;
};
struct PlayerKnockback {
	size_t playerIndex;
};

// Sum type of interanl game events
enum class InternalGameEventType { DELETE_BULLET, PLAYER_KNOCKBACK };
struct InternalGameEvent {
	iow::InternalGameEventType type;
	union {
		DeleteBullet deleteBullet;
		PlayerKnockback playerKnockback;
	};
};
} // namespace iow
