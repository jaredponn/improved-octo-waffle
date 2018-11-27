#pragma once

#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "input.h"


/** gameinput.h
 * Enums and related data types for game inputs and game events. For parsing the
 * events / causing the effects, look at the parsegamekeys.h/.cpp file
 */

namespace iow
{

enum class PlayerGameEvents : unsigned int {
	MOVE_PLAYER_UP,
	MOVE_PLAYER_RIGHT,
	MOVE_PLAYER_LEFT,
	MOVE_PLAYER_DOWN,

	MOVE_PLAYER_UP_LEFT,
	MOVE_PLAYER_DOWN_LEFT,
	MOVE_PLAYER_UP_RIGHT,
	MOVE_PLAYER_DOWN_RIGHT,
	PLAYER_SHOOT,

	NO_ACTION
};

using SingleKeyBind = std::pair<iow::KeyState, iow::PlayerGameEvents>;

// key,
using SFKeyAndKeyStatePair = std::pair<sf::Keyboard::Key, iow::KeyState>;

using KeyChord =
	std::pair<std::vector<SFKeyAndKeyStatePair>, iow::PlayerGameEvents>;

} // namespace iow
