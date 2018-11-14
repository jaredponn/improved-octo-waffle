#include "ecs.h"
#include <iostream>

namespace iow
{
iow::ECS::ECS(size_t capacity) : Components(capacity)
{

	for (size_t i = 0; i < capacity; ++i) {
		m_free_indices.push(i);
	}

	// TODO
	// make sure you intialize the compoenets as well. probably use xmacros
	// to do this
}

size_t iow::ECS::create_new_entity()
{
	size_t tmp = m_free_indices.top();
	m_free_indices.pop();
	return tmp;
}


void iow::ECS::runECS(sf::Time dt, const KeyBuffer &keyBufInput)
{
	float t = dt.asMicroseconds();

	size_t newentity = create_new_entity();
	c_HP.add_element_at_sparse_vector(newentity, 1);
	c_Position.add_element_at_sparse_vector(newentity, sf::Vector2f(2, 3));
}

} // namespace iow
