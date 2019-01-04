#pragma once

#include "ecs.h"
#include "internalgameevents.h"
#include <stack>

namespace iow
{


void parseInternalGameEvents(iow::ECS &ecs,
			     std::stack<iow::InternalGameEvent> &gameEvents);

} // namespace iow
