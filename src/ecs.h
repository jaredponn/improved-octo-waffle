#pragma once
#include <stack>
#include "packedvector.h"

namespace iow
{
class ECS
{
    private:
	std::stack<size_t> m_free_indices;

    public:
	ECS(size_t capacity);
	// TODO
	// put more component packed vectors here


	// TODO add delete and add entity functions here
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
