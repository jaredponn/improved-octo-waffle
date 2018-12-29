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
//    Collisions between player and wall
// -----------------------------------------
static inline void checkAndResolveCollisionOfOneAgainstEntities(
	iow::CollisionBox &oneCollisionBox, iow::Position &onePosition,
	const iow::PackedVector<iow::CollisionBox> &pkdCollision)
{
	const std::vector<iow::CollisionBox> &pkdColData =
		pkdCollision.get_packed_data();

	for (auto &i : pkdColData) {
		auto tmp =
			iow::checkAndResolveCollisionDelta(oneCollisionBox, i);
		if (tmp) {
			onePosition += tmp.value();
			oneCollisionBox.setPosition(onePosition);
		}
	}
}

// -----------------------------------------
//    Steering behaviours
// -----------------------------------------

static inline void updateVelocityToSeek(
	iow::PackedVector<iow::Speed> &speedPkdVec,
	iow::PackedVector<bool> const &entitySet,
	iow::PackedVector<iow::Position> const &posPkdVec,
	iow::PackedVector<iow::SteeringBehaviour::SteeringBehaviour> const
		&steeringPkdVec,
	const iow::Position &seekToPos)
{

	auto const entitySetPkdVecLen = entitySet.get_packed_data_size();


	for (size_t i = 0; i < entitySetPkdVecLen; i++) {
		size_t const entitySetGlobalIndex =
			entitySet.get_global_index_from_packed_index(i);
		sf::Vector2f const steeringVel =
			iow::SteeringBehaviour::calculateSeekSteeringVelocity(
				steeringPkdVec[entitySetGlobalIndex],
				speedPkdVec[entitySetGlobalIndex],
				iow::SteeringBehaviour::calculatePositionDelta(
					seekToPos,
					posPkdVec[entitySetGlobalIndex]));
		speedPkdVec[entitySetGlobalIndex] += steeringVel;
	}
}

static inline void updateVelocityToFlee(
	iow::PackedVector<iow::Speed> &speedPkdVec,
	iow::PackedVector<bool> const &entitySet,
	iow::PackedVector<iow::Position> const &posPkdVec,
	iow::PackedVector<iow::SteeringBehaviour::SteeringBehaviour> const
		&steeringPkdVec)
{

	auto const entitySetPkdVecLen = entitySet.get_packed_data_size();

	for (size_t i = 0; i < entitySetPkdVecLen; ++i) {
		for (size_t j = 0; j < entitySetPkdVecLen; ++j) {
			if (i != j) {


				size_t const entitySetGlobalIndex =
					entitySet
						.get_global_index_from_packed_index(
							i);

				size_t const otherEntitySetGlobalIndex =
					entitySet
						.get_global_index_from_packed_index(
							j);

				sf::Vector2f const steeringVel = iow::
					SteeringBehaviour::calculateFleeVelocity(
						steeringPkdVec
							[entitySetGlobalIndex],
						speedPkdVec
							[entitySetGlobalIndex],
						iow::SteeringBehaviour::calculatePositionDelta(
							posPkdVec
								[otherEntitySetGlobalIndex],
							posPkdVec
								[entitySetGlobalIndex]));

				speedPkdVec[entitySetGlobalIndex] +=
					steeringVel;
			}
		}
	}
}


//    Collisions between bullet and wall
// -----------------------------------------
static inline void checkAndResolveCollisionBulletAgainstEntities(
	iow::PackedVector<bool> &bullet,
	iow::PackedVector<iow::CollisionCir> &bulletCir,
	const iow::PackedVector<iow::CollisionBox> &pkdCollision,
	iow::PackedVector<iow::Position> &posVec,
	iow::PackedVector<iow::Direction> &dirVec,
	iow::PackedVector<iow::Speed> &speedVec,
	iow::PackedVector<iow::Appearance> &appVec)
{
	// the bullet position is updated ..
	const auto &pkdColData = pkdCollision.get_packed_data();
	const auto &bulletData = bulletCir.get_packed_data();
	for (size_t i = 0; i < bullet.get_packed_data().size(); ++i) {

		// TODO JARED make this work less bad
		const iow::CollisionCir tempBullet = bulletData[i];
		for (iow::CollisionBox j : pkdColData) {
			if (iow::checkCollisionBullet(tempBullet, j)) {
				// deleteBullet(i, &bullet, &bulletCir);
				size_t tempSparseInd =
					bullet.get_global_index_from_packed_index(
						i);
				bullet.delete_element_at_sparse_vector(
					tempSparseInd);
				bulletCir.delete_element_at_sparse_vector(
					tempSparseInd);
				posVec.delete_element_at_sparse_vector(
					tempSparseInd);
				dirVec.delete_element_at_sparse_vector(
					tempSparseInd);
				speedVec.delete_element_at_sparse_vector(
					tempSparseInd);
				appVec.delete_element_at_sparse_vector(
					tempSparseInd);
				break;
			}
		}
	}
}
// -----------------------------------------
//    Update bullet CollisionCir position
// -----------------------------------------
static inline void updateCirclePosFromPosition(
	const iow::PackedVector<bool> &bullet,
	iow::PackedVector<iow::CollisionCir> &bulletCir,
	const iow::PackedVector<iow::Position> &positionPackedVector)
{
	for (size_t i = 0; i < bullet.get_packed_data().size(); ++i) {
		bulletCir[bulletCir.get_global_index_from_packed_index(i)]
			.setPosition(
				positionPackedVector
					[bulletCir
						 .get_global_index_from_packed_index(
							 i)]);
	}
}
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
