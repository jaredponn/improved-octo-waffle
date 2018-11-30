#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <tuple>
#include <vector>

namespace iow
{

constexpr size_t MAX_NUMBER_KEYS = sf::Keyboard::KeyCount;


enum class KeyState : unsigned int {
	UP = 0b00,
	PRESSED = 0b01,
	DOWN = 0b11,
	RELEASED = 0b10,

	INVALID_STATE = 0b111
};

using KeyBuffer = std::array<unsigned int, MAX_NUMBER_KEYS>;

class InputManager
{

    public:
	// initilizes the key buffer
	static void initInputManager();


	// gets the entire key buffer
	static const iow::KeyBuffer &getKeyBuffer();

	// gets the given key state (up press down released)
	static KeyState getKeyState(const sf::Keyboard::Key key);

	// sets a key to the given state. WARNING: unsafe and does not do bounds
	// checking
	static void setKeyState(const sf::Keyboard::Key key,
				const iow::KeyState keystate);

	// convience function that "resets" the key state to UP. WARNING: unsafe
	// and does not do bounds chekcing
	static void resetKeyState(const sf::Keyboard::Key key);

	// updates the input buffer. must be called once evrey frame
	static void shiftAndUpdateInputbuffer();

    private:
	InputManager();
	static void pollForInputBuffer();
	static void shiftInputBuffer();
	static KeyState identifyKeyState(unsigned int val);
};

} // namespace iow
