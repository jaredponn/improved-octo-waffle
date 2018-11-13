#include "input.h"
#include "logger.h"
#include <memory.h>


namespace iow
{

static std::unique_ptr<KeyBuffer> KEY_INPUT_BUFFER;

void iow::InputManager::initInputManager()
{
	KEY_INPUT_BUFFER = std::make_unique<KeyBuffer>();
	KEY_INPUT_BUFFER->fill(0);
}

iow::InputManager::KeyState
iow::InputManager::getKeyState(const sf::Keyboard::Key &key)
{
	unsigned int tmp = KEY_INPUT_BUFFER->at((unsigned int)key);
	return identifyKeyState(tmp);
}

iow::InputManager::KeyState
iow::InputManager::identifyKeyState(unsigned int val)
{
	unsigned int tmp = val & 0b11;

	switch (tmp) {
	case (unsigned int)iow::InputManager::KeyState::UP:
		return iow::InputManager::KeyState::UP;
		break;
	case (unsigned int)iow::InputManager::KeyState::PRESSED:
		return iow::InputManager::KeyState::PRESSED;
		break;

	case (unsigned int)iow::InputManager::KeyState::DOWN:
		return iow::InputManager::KeyState::DOWN;
		break;
	case (unsigned int)iow::InputManager::KeyState::RELEASED:
		return iow::InputManager::KeyState::RELEASED;
		break;
	default:
		Logger::logMessage(
			"ERROR in InputHandler. Invalid key state... Returning Keystate::UP ");
		return iow::InputManager::KeyState::UP;
	}
}

void iow::InputManager::shiftAndUpdateInputbuffer()
{
	iow::InputManager::shiftInputBuffer();
	iow::InputManager::pollForInputBuffer();
}

void iow::InputManager::pollForInputBuffer()
{
	for (auto i = 0; i < sf::Keyboard::Key::KeyCount; ++i) {
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i)) {
			KEY_INPUT_BUFFER->data()[i] |= 1;
		}
	}
}
void iow::InputManager::shiftInputBuffer()
{
	for (auto i = 0; i < sf::Keyboard::Key::KeyCount; ++i) {
		KEY_INPUT_BUFFER->data()[i] <<= 1;
	}
}

}; // namespace iow
