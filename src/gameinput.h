#pragma once

#include <vector>
#include <tuple>
#include "input.h"

namespace iow
{

enum class PlayerGameEvents : unsigned int {
	MOVE_PLAYER_UP,
	MOVE_PLAYER_RIGHT,
	MOVE_PLAYER_LEFT,
	MOVE_PLAYER_DOWN,
	PLAYER_SHOOT,

	NO_ACTION
};

using KeyBind = std::pair<iow::KeyState, iow::PlayerGameEvents>;

using KeyChord = std::tuple<std::vector<iow::KeyState>, PlayerGameEvents>;


} // namespace iow
