#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <stack>

#include "components.h"
#include "extrastate.h"
#include "input.h"
#include "packedvector.h"
#include "resourcemanager.h"

namespace iow
{

class ECS : public iow::Components, public iow::ExtraState
{
    public:
	ECS(size_t capacity);

	// TODO implement
	void initECS(sf::RenderWindow &window,
		     iow::ResourceManager &resourceManager);

	// TODO implement
	void runECS(float dt, sf::RenderWindow &window,
		    iow::ResourceManager &resourceManager);

	void runGameLogic(float dt, iow::ResourceManager &resourceManager);

    public:
	// gives you an index to a new entity in the ECS
	size_t create_new_entity();
	size_t delete_entity_at(size_t index);
	void add_component_to(size_t index);

    private:
	std::stack<size_t> m_free_indices;
};

}; // namespace iow
