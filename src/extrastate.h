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
	iow::Camera m_camera;
};

} // namespace iow
