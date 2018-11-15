#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.h"
#include "packedvector.h"
#include "components.h"
#include "logger.h"

/** systems.h
 * Systems to run over the ECS.
 */

namespace iow
{

// -----------------------------------------
//    Position update systems
// -----------------------------------------
static inline void
updateAppearanceFromPosition(iow::PackedVector<Appearance> &pkdAppearance,
			     iow::PackedVector<Position> &pkdPos,
			     iow::Camera &camera)
{
	auto posPkdData = pkdPos.get_packed_data();
	auto posPkdIndicies = pkdPos.get_packed_indicies();

	if (posPkdData.size() != posPkdIndicies.size())
		Logger::logMessage(
			"ERROR in updateAppearanceFromPosition. Position packed vector is of different size, buggy programis going to follow ");

	sf::Vector2<float> npos;
	sf::Vector2f lengthOffset;

	for (size_t i = 0; i < posPkdIndicies.size(); ++i) {
		npos = (posPkdData[i] - (camera.position))
		       + (camera.windowsize * 0.5f);

		lengthOffset = sf::Vector2<float>(
			-static_cast<float>(pkdAppearance[posPkdIndicies[i]]
						    .getTextureRect()
						    .width)
				/ 2.f,
			static_cast<float>(pkdAppearance[posPkdIndicies[i]]
						   .getTextureRect()
						   .height)
				/ 2.f);
		std::cout << lengthOffset.x << std::endl;
		std::cout << lengthOffset.y << std::endl;

		npos += lengthOffset;
		npos.x *= camera.scale.x;
		npos.y *= camera.scale.y;


		pkdAppearance[posPkdIndicies[i]].setPosition(npos);
	}
}

// -----------------------------------------
//    Camera update system
// -----------------------------------------
static inline void updateCamera(Camera &camera, const sf::Vector2f &pos,
				const sf::Vector2u windowSize)
{
	camera.position = pos;
	camera.windowsize = sf::Vector2f(static_cast<float>(windowSize.x),
					 static_cast<float>(windowSize.y));

	camera.windowsize.x *= camera.scale.x;
	camera.windowsize.y *= camera.scale.y;
}


// -----------------------------------------
//    Render systems
// -----------------------------------------
static inline void renderEntityToSFMLRenderBuffer(sf::RenderWindow &window,
						  const sf::Sprite &sprite,
						  const iow::Camera &camera)
{
	sf::Sprite tmp = sprite;
	tmp.move(camera.position);

	window.draw(sprite);
}

static inline void renderSystem(const iow::PackedVector<sf::Sprite> &data,
				sf::RenderWindow &window,
				const iow::Camera &camera)
{
	for (const auto &i : data.get_packed_data()) {
		renderEntityToSFMLRenderBuffer(window, i, camera);
	}
}


} // namespace iow
