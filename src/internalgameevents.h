#pragma once

#include <stack>

namespace iow
{

struct DeleteBullet {
	size_t bulletEntity;
};

// Sum type of interanl game events
enum class InternalGameEventType { DELETE_BULLET };
struct InternalGameEvent {
	iow::InternalGameEventType type;
	union {
		DeleteBullet deleteBullet;
	};
};
} // namespace iow
