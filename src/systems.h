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
//    Collisions
// -----------------------------------------
static inline void checkAndResolveCollisionOfOneAgainstEntities(
	const iow::CollisionBox &oneCollisionBox, iow::Position &onePosition,
	const iow::PackedVector<iow::CollisionBox> &pkdCollision)
{
	const std::vector<iow::CollisionBox> &pkdColData =
		pkdCollision.get_packed_data();


	for (auto &i : pkdColData) {
		auto tmp =
			iow::checkAndResolveCollisionDelta(oneCollisionBox, i);
		if (tmp) {
			onePosition += tmp.value();
			break;
		}
	}
}

// -----------------------------------------
//    Computing Position deltas
// -----------------------------------------


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

static inline void
updateCollisionBoxFromPosition(iow::PackedVector<CollisionBox> &pkdCollision,
			       const iow::PackedVector<Position> &pkdPos)
{

	const auto &colPkdData = pkdCollision.get_packed_data();
	const auto &colPkdIndices = pkdCollision.get_packed_indicies();

	if (colPkdData.size() != colPkdIndices.size())
		Logger::logMessage(
			"ERROR in updateCollisionBoxFromPosition. Position packed vector is of different size, buggy program is going to follow ");

	for (size_t i = 0; i < colPkdIndices.size(); ++i) {
		pkdCollision[colPkdIndices[i]] =
			setCollisionBoxPositionFromPosition(
				colPkdData[i], pkdPos[colPkdIndices[i]]);
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

	/* sf::Vector2f lengthOffset = sf::Vector2f(0, 0); */
	// uncommenting this code block sets it so that it will rende rnicelyin
	// the center of the screen, howevre it will not play nicely with hte
	// collision system
	// TODO -- not exactly too sure how to go about fixing this....
	/* sf::Vector2f lengthOffset = sf::Vector2f( */
	/* 	-static_cast<float>(sprite.getTextureRect().width) / 2.f, */
	/* 	static_cast<float>(sprite.getTextureRect().height) / 2.f); */

	// Uncommenting this block of code will make collisions weird. For some
	// reason, all entites have to have the heigh pushed in to match the
	// collision box size
	sf::Vector2f lengthOffset = sf::Vector2f(
		0.0, static_cast<float>(sprite.getTextureRect().height));

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

static inline void
debugRenderSystem(const iow::PackedVector<sf::RectangleShape> &data,
		  sf::RenderWindow &window, const iow::Camera &camera)
{
	for (const auto &i : data.get_packed_data()) {
		sf::Sprite tmp;
		sf::Image tmpimage;
		sf::Texture ttmp;

		tmpimage.create(i.getSize().x, i.getSize().y,
				sf::Color(255, 0, 0));
		ttmp.loadFromImage(tmpimage);
		tmp.setTexture(ttmp);
		tmp.setColor(sf::Color::Red);
		tmp.setPosition(i.getPosition());

		renderEntityToSFMLRenderBuffer(window, tmp, camera);
	}
}

} // namespace iow
