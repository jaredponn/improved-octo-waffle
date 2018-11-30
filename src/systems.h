#pragma once

#include <SFML/Graphics.hpp>

#include "components.h"
#include "graphics.h"
#include "logger.h"
#include "packedvector.h"

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
			     const iow::PackedVector<Position> &pkdPos)
{
	const auto &posPkdData = pkdPos.get_packed_data();
	const auto &posPkdIndicies = pkdPos.get_packed_indicies();

	if (posPkdData.size() != posPkdIndicies.size())
		Logger::logMessage(
			"ERROR in updateAppearanceFromPosition. Position packed vector is of different size, buggy programis going to follow ");

	for (size_t i = 0; i < posPkdIndicies.size(); ++i) {
		pkdAppearance[posPkdIndicies[i]].setPosition(posPkdData[i]);
	}
}

static inline void
updatePositionFromSpeed(const float dt,
			iow::PackedVector<Position> &positionPackedVector,
			const iow::PackedVector<Speed> &speedPackedVector)
{

	const auto &speedPackedIndicies =
		speedPackedVector.get_packed_indicies();
	const auto &speedPackedData = speedPackedVector.get_packed_data();

	if (speedPackedIndicies.size() != speedPackedData.size())
		Logger::logMessage(
			"ERROR in update position from speed. Velocity packed data is not the same size");
	for (size_t i = 0; i < speedPackedData.size(); ++i) {
		positionPackedVector[speedPackedIndicies[i]] +=
			speedPackedData[i] * dt;
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

	sf::Vector2f lengthOffset = sf::Vector2f(
		-static_cast<float>(sprite.getTextureRect().width) / 2.f,
		static_cast<float>(sprite.getTextureRect().height) / 2.f);

	sf::Vector2f npos;
	npos = (sprite.getPosition() - (camera.position))
	       + (camera.windowsize * 0.5f);

	npos += lengthOffset;
	npos.x *= camera.scale.x;
	npos.y *= camera.scale.y;

	auto newsprite = sprite;
	newsprite.setPosition(npos);

	window.draw(newsprite);
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
