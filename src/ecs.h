#pragma once
#include <stack>
#include <cstdint>
#include <SFML/Graphics.hpp>

#include "packedvector.h"
#include "input.h"

namespace iow
{


enum class ComponentTypes : uint64_t {
	HP = 0x0000001,
	POSITION = 0x0000010,
	SPEED = 0x0000100,
	CANSHOOT = 0x0001000,
	HASCOLLISION = 0x0010000,
};

class ECS
{
    public:
	ECS(size_t capacity);

	// TODO implement
	void runECS(sf::Time dt, const iow::KeyBuffer &keyBufInput);

	// TODO add delete and add entity functions here
	void create_new_entity(uint64_t components);
	void add_component_to(size_t index, ComponentTypes component);

	// TODO
	// put more component packed vectors here
	struct Components {
		iow::PackedVector<float> HP;
		iow::PackedVector<sf::Vector2f> Position;
	};

    private:
	std::stack<size_t> m_free_indices;
};

ECS::ECS(size_t capacity)
{
	for (size_t i = 0; i < capacity; ++i) {
		m_free_indices.push(i);
	}

	// TODO
	// make sure you intialize the compoenets as well. probably use xmacros
	// to do this
}


}; // namespace iow
