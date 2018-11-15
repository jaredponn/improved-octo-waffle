#pragma once
#include <SFML/Graphics.hpp>

#include "camera.h"


namespace iow
{
class ExtraState
{
    public:
	ExtraState();

	// state
	size_t m_player_entity;
	iow::Camera m_camera;
};

} // namespace iow
