#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace iow
{

using KeyBuffer = std::array<unsigned int, sf::Keyboard::KeyCount>;

class InputManager
{
	enum class KeyState : unsigned int {
		UP = 0b00,
		PRESSED = 0b01,
		DOWN = 0b11,
		RELEASED = 0b10
	};

    public:
	// initilizes the key buffer
	static void initInputManager();


	// gets the entire key buffer
	static const iow::KeyBuffer &getKeyBuffer();

	// gets the given key state
	static InputManager::KeyState getKeyState(const sf::Keyboard::Key &key);

	static InputManager::KeyState identifyKeyState(unsigned int val);

	// updates the input buffer. must be called once evrey frame
	static void shiftAndUpdateInputbuffer();

    private:
	InputManager();
	static void pollForInputBuffer();
	static void shiftInputBuffer();
};

} // namespace iow
