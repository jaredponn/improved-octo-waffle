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

const iow::KeyBuffer &iow::InputManager::getKeyBuffer()
{
	return *KEY_INPUT_BUFFER;
}

iow::KeyState iow::InputManager::getKeyState(const sf::Keyboard::Key &key)
{
	return identifyKeyState(
		KEY_INPUT_BUFFER->at(static_cast<unsigned int>(key)));
}

iow::KeyState iow::InputManager::identifyKeyState(unsigned int val)
{
	return static_cast<iow ::KeyState>(val & 0b11);
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
