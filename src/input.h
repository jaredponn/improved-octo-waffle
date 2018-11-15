#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace iow
{

constexpr size_t MAX_NUMBER_KEYS = sf::Keyboard::KeyCount;

using KeyBuffer = std::array<unsigned int, MAX_NUMBER_KEYS>;

enum class KeyState : unsigned int {
	UP = 0b00,
	PRESSED = 0b01,
	DOWN = 0b11,
	RELEASED = 0b10,

	INVALID_STATE = 0b111
};

enum class PlayerGameEvents : unsigned int {
	MOVE_PLAYER_UP,
	MOVE_PLAYER_RIGHT,
	MOVE_PLAYER_LEFT,
	MOVE_PLAYER_DOWN,
	PLAYER_SHOOT, // TODO HAIYANG

	NO_ACTION
};

class InputManager
{

    public:
	// initilizes the key buffer
	static void initInputManager();


	// gets the entire key buffer
	static const iow::KeyBuffer &getKeyBuffer();

	// gets the given key state
	static KeyState getKeyState(const sf::Keyboard::Key &key);

	static KeyState identifyKeyState(unsigned int val);

	// updates the input buffer. must be called once evrey frame
	static void shiftAndUpdateInputbuffer();

    private:
	InputManager();
	static void pollForInputBuffer();
	static void shiftInputBuffer();
};

} // namespace iow
