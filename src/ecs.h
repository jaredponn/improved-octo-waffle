#pragma once
#include <stack>
#include <cstdint>
#include <SFML/Graphics.hpp>

#include "packedvector.h"
#include "input.h"
#include "components.h"

namespace iow
{


class ECS : private iow::Components
{
    public:
	ECS(size_t capacity);

	// TODO implement
	void runECS(sf::Time dt, const KeyBuffer &keyBufInput);

    private:
	// TODO add delete and add entity functions here
	void create_new_entity(uint64_t components);
	void add_component_to(size_t index);

    private:
	std::stack<size_t> m_free_indices;
};

ECS::ECS(size_t capacity) : Components(capacity)
{

	for (size_t i = 0; i < capacity; ++i) {
		m_free_indices.push(i);
	}

	// TODO
	// make sure you intialize the compoenets as well. probably use xmacros
	// to do this
}


}; // namespace iow
