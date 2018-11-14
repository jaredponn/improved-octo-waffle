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


void iow::ECS::runECS(sf::Time dt, const KeyBuffer &keyBufInput)
{
	float t = dt.asMicroseconds();
}

} // namespace iow
