#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <stack>

#include "components.h"
#include "graphics.h"
#include "internalgameevents.h"
#include "logger.h"
#include "packedvector.h"
#include "pathfinding.h"
#include "tilemappathfinding.h"

/** systems.h
 * Systems to run over the ECS.
 */

namespace iow
{

// -----------------------------------------
//    Collisions between player and wall
// -----------------------------------------
static inline void checkAndResolveCollisionOfPlayerAgainstWall(
	iow::CollisionBox &oneCollisionBox, sf::Vector2f &velocity,
	sf::Vector2f &prevVelocity, const float dt, float &playerDeltaTime,
	const iow::PackedVector<iow::CollisionBox> &pkdCollision)
{
	const std::vector<iow::CollisionBox> &pkdColData =
		pkdCollision.get_packed_data();

	for (auto &i : pkdColData) {
		auto tmp = iow::checkAndResolveCollisionPlayerWithWall(
			oneCollisionBox, i, velocity, prevVelocity, dt,
			playerDeltaTime);
		if (tmp) {
			// std::cout << " old player velocity: " << velocity.x
			//<< " " << velocity.y << std::endl;
			velocity = tmp.value(); // update the velocity of the
						// player
			// std::cout << " new player velocity: " << velocity.x
			//<< " " << velocity.y << std::endl;
		}
	}
}

// -----------------------------------------
//    collision between player and enemy
// -----------------------------------------
/*
static inline void checkAndResolveCollisionOfPlayerAgainstZombie(
	iow::CollisionBox &oneCollisionBox, iow::Position &onePosition,
	const sf::Vector2f &velocity, const iow::PackedVector<bool> &enemyBool,
	const iow::PackedVector<iow::CollisionBox> &enemyPkdCollision,
	const float dt)
{
	// return new dttttttttttttt
	for (size_t i = 0; i < enemyBool.get_packed_data().size(); ++i) {
		auto tmp = iow::checkAndResolveCollisionPlayerWithWall(
			oneCollisionBox,
			enemyPkdCollision
				[enemyBool.get_global_index_from_packed_index(
					i)],
			velocity, dt, 13);
		if (tmp) {
			onePosition += tmp.value();
			oneCollisionBox.setPosition(onePosition);
		}
	}
}
*/

/*

static inline void checkAndResolveCollisionOfPlayerAgainstEntities(
	iow::CollisionBox &oneCollisionBox, iow::Position &onePosition,
	const iow::PackedVector<bool> &enemyBool,
	const iow::PackedVector<iow::CollisionBox> &enemyPkdCollision,
	const float dt)
{
	// return new dttttttttttttt
	for (size_t i = 0; i < enemyBool.get_packed_data().size(); ++i) {
		auto tmp = iow::checkAndResolveCollisionDelta(
			oneCollisionBox,
			enemyPkdCollision
				[enemyBool.get_global_index_from_packed_index(
					i)],
			13);
		if (tmp) {
			onePosition += tmp.value();
			oneCollisionBox.setPosition(onePosition);
		}
	}
}
 */

// -----------------------------------------
//    collision between player and enemy
// -----------------------------------------
static inline void updateEnemyBoxPosFromPosition(
	const iow::PackedVector<bool> &enemyBool,
	iow::PackedVector<iow::CollisionBox> &enemyColBox,
	const iow::PackedVector<iow::Position> &positionPackedVector)
{
	for (size_t i = 0; i < enemyBool.get_packed_data().size(); ++i) {
		enemyColBox[enemyColBox.get_global_index_from_packed_index(i)]
			.setPosition(
				positionPackedVector
					[enemyColBox
						 .get_global_index_from_packed_index(
							 i)]);
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

		sf::Vector2f posDelta =
			iow::SteeringBehaviour::calculatePositionDelta(
				seekToPos, posPkdVec[entitySetGlobalIndex]);

		sf::Vector2f const steeringVel =
			iow::SteeringBehaviour::calculateSeekSteeringVelocity(
				steeringPkdVec[entitySetGlobalIndex],
				speedPkdVec[entitySetGlobalIndex], posDelta);
		speedPkdVec[entitySetGlobalIndex] += steeringVel;
	}
}
static inline void updateVelocityToSeekToOtherPositionComponent(
	iow::PackedVector<iow::Speed> &speedPkdVec,
	iow::PackedVector<bool> const &entitySet,
	iow::PackedVector<iow::Position> const &posPkdVec,
	iow::PackedVector<iow::SteeringBehaviour::SteeringBehaviour> const
		&steeringPkdVec,
	iow::PackedVector<iow::Position> const &seekToPosPkdVec)
{

	auto const entitySetPkdVecLen = entitySet.get_packed_data_size();

	for (size_t i = 0; i < entitySetPkdVecLen; i++) {
		size_t const entitySetGlobalIndex =
			entitySet.get_global_index_from_packed_index(i);

		sf::Vector2f const a = posPkdVec[entitySetGlobalIndex];
		sf::Vector2f const b = seekToPosPkdVec[entitySetGlobalIndex];
		std::cout << "a, b entity in steer" << std::endl;
		std::cout << a.x << " " << a.y << std::endl;
		std::cout << b.x << " " << b.y << std::endl;

		sf::Vector2f const posDelta =
			iow::SteeringBehaviour::calculatePositionDelta(b, a);
		std::cout << "posdelta" << std::endl;
		std::cout << posDelta.x << " " << a.y << std::endl;
		std::cout << posDelta.x << " " << b.y << std::endl;

		sf::Vector2f const steeringVel =
			iow::SteeringBehaviour::calculateSeekSteeringVelocity(
				steeringPkdVec[entitySetGlobalIndex],
				speedPkdVec[entitySetGlobalIndex], posDelta);
		std::cout << "steerinvel" << std::endl;
		std::cout << steeringVel.x << " " << a.y << std::endl;
		std::cout << steeringVel.x << " " << b.y << std::endl;


		speedPkdVec[entitySetGlobalIndex] += steeringVel;
	}
}


static inline void updateVelocityToFleeAgainstItself(
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

static inline void updateVelocityToFleeFromTileMapWalls(
	iow::PackedVector<iow::Speed> &speedPkdVec,
	iow::PackedVector<bool> const &fleeingEntitySet,
	iow::PackedVector<iow::CollisionBox> const &tilemapcollision,
	iow::PackedVector<iow::Position> const &posPkdVec,
	iow::PackedVector<iow::SteeringBehaviour::SteeringBehaviour> const
		&steeringPkdVec)
{
	std::vector<size_t> tileMapCollisionPkdVec =
		tilemapcollision.get_packed_indicies();

	std::vector<size_t> fleeingEntitySetPkdVec =
		fleeingEntitySet.get_packed_indicies();

	for (auto const &i : tileMapCollisionPkdVec) {
		sf::Vector2f const wallPos =
			iow::getCollisionBoxCenter(tilemapcollision[i]);

		for (auto const &j : fleeingEntitySetPkdVec) {

			sf::Vector2f const steeringVel =
				iow::SteeringBehaviour::calculateFleeVelocity(
					steeringPkdVec[i], speedPkdVec[j],
					iow::SteeringBehaviour::
						calculatePositionDelta(
							wallPos, posPkdVec[j]));
			speedPkdVec[j] += steeringVel / 100.f;
		}
	}
}

// -----------------------------------------
//    Collisions between bullet and wall
// -----------------------------------------

static inline void checkAndResolveCollisionBulletAgainstWallsAndZombies(
	iow::PackedVector<bool> &bullet,
	iow::PackedVector<iow::CollisionCir> &bulletCir,
	iow::PackedVector<float> &bulletDamage,
	iow::PackedVector<bool> &enemyBool,
	iow::PackedVector<iow::CollisionBox> &enemyColBox,
	iow::PackedVector<float> &enemyHP,

	const iow::PackedVector<iow::CollisionBox> &pkdCollision,
	std::stack<iow::InternalGameEvent> &internalGameEvents)
{
	// the bullet position is updated ..
	const auto &pkdColData = pkdCollision.get_packed_data();
	const auto &bulletData = bulletCir.get_packed_data();
	for (size_t i = 0; i < bullet.get_packed_data().size(); ++i) {

		size_t tempBulletSparseInd =
			bullet.get_global_index_from_packed_index(i);
		const iow::CollisionCir tempBullet = bulletData[i];
		const auto &enemyData = enemyColBox.get_packed_data();
		bool tempBulletDelete = false;


		for (size_t j = 0; j < enemyBool.get_packed_data().size();
		     ++j) {
			size_t tempEnemySparseInd =
				enemyBool.get_global_index_from_packed_index(j);

			if (iow::checkCollisionBullet(tempBullet,
						      enemyData[j])) {
				enemyHP[tempEnemySparseInd] -=
					bulletDamage[tempBulletSparseInd];

				if (enemyHP[tempEnemySparseInd] <= 0) {
					internalGameEvents.push((
						struct InternalGameEvent){
						.type = iow::
							InternalGameEventType::
								DELETE_ENEMY,
						.deleteEnemy = (DeleteEnemy){
							tempEnemySparseInd}});
				}
				internalGameEvents.push((
					struct InternalGameEvent){
					.type = iow::InternalGameEventType::
						DELETE_BULLET,
					.deleteBullet = (DeleteBullet){
						tempBulletSparseInd}});
				tempBulletDelete = true;
				break;
			}
		}

		if (!tempBulletDelete) {
			for (iow::CollisionBox j : pkdColData) {
				if (iow::checkCollisionBullet(tempBullet, j)) {
					// deleteBullet(i, &bullet, &bulletCir);
					internalGameEvents.push((
						struct InternalGameEvent){
						.type = iow::
							InternalGameEventType::
								DELETE_BULLET,
						.deleteBullet = (DeleteBullet){
							tempBulletSparseInd}});
					break;
				}
			}
		}
	}
}
/*
static inline void checkAndResolveCollisionBulletAgainstWallsAndZombies(
	iow::PackedVector<bool> &bullet,
	iow::PackedVector<iow::CollisionCir> &bulletCir,
	iow::PackedVector<float> &bulletDamage,
	iow::PackedVector<bool> &enemyBool,
	iow::PackedVector<iow::CollisionBox> &enemyColBox,
	iow::PackedVector<float> &enemyHP,
	const iow::PackedVector<iow::CollisionBox> &pkdCollision,
	std::stack<iow::InternalGameEvent> &internalGameEvents)
{
	// the bullet position is updated ..
	const auto &pkdColData = pkdCollision.get_packed_data();
	const auto &bulletData = bulletCir.get_packed_data();
	const auto &enemyData = enemyColBox.get_packed_data();
	for (size_t i = 0; i < bullet.get_packed_data().size(); ++i) {

		const iow::CollisionCir tempBullet = bulletData[i];

		size_t tempBulletSparseInd =
			bullet.get_global_index_from_packed_index(i);
		bool tempBulletDelete = false;

		for (size_t j = 0; j < enemyBool.get_packed_data().size();
		     ++j) {
			size_t tempSparseInd =
				enemyBool.get_global_index_from_packed_index(j);
			if (iow::checkCollisionBullet(tempBullet,
						      enemyData[j])) {
				std::cout << "size of the enemyBool "
					  << enemyBool.get_packed_data().size()
					  << std::endl;

				std::cout << "size of the HPPP "
					  << enemyHP.get_packed_data().size()
					  << std::endl;
				std::cout << "enemy " << j << " ,prev HP= "
					  << enemyHP[tempSparseInd]
					  << std::endl;
				enemyHP[tempSparseInd] -=
					bulletDamage[tempBulletSparseInd];
				std::cout << "enemy " << j << " ,after  HP= "
					  << enemyHP[tempSparseInd]
					  << std::endl;
				if (enemyHP[tempSparseInd] <= 0) {
					enemyBool
						.delete_element_at_sparse_vector(
							tempSparseInd);
					enemyColBox
						.delete_element_at_sparse_vector(
							tempSparseInd);
					enemyHP.delete_element_at_sparse_vector(
						tempSparseInd);
					posVec.delete_element_at_sparse_vector(
						tempSparseInd);
					dirVec.delete_element_at_sparse_vector(
						tempSparseInd);
					speedVec.delete_element_at_sparse_vector(
						tempSparseInd);
					appVec.delete_element_at_sparse_vector(
						tempSparseInd);
				}
				bullet.delete_element_at_sparse_vector(
					tempBulletSparseInd);
				bulletCir.delete_element_at_sparse_vector(
					tempBulletSparseInd);

				posVec.delete_element_at_sparse_vector(
					tempBulletSparseInd);
				dirVec.delete_element_at_sparse_vector(
					tempBulletSparseInd);
				speedVec.delete_element_at_sparse_vector(
					tempBulletSparseInd);
				appVec.delete_element_at_sparse_vector(
					tempBulletSparseInd);
				tempBulletDelete = true;
				break;
			}
		}
		if (!tempBulletDelete) {
			for (iow::CollisionBox j : pkdColData) {
				if (iow::checkCollisionBullet(tempBullet, j)) {
					bullet.delete_element_at_sparse_vector(
						tempBulletSparseInd);
					bulletCir
						.delete_element_at_sparse_vector(
							tempBulletSparseInd);
					posVec.delete_element_at_sparse_vector(
						tempBulletSparseInd);
					dirVec.delete_element_at_sparse_vector(
						tempBulletSparseInd);
					speedVec.delete_element_at_sparse_vector(
						tempBulletSparseInd);
					appVec.delete_element_at_sparse_vector(
						tempBulletSparseInd);
					break;
				}
			}
		}
	}
}
*/


// -----------------------------------------
//   Debug HP
// -----------------------------------------

static inline void debugEnemyHP(const iow::PackedVector<float> &hp)
{
	const auto hpData = hp.get_packed_data();
	for (size_t i = 0; i < hpData.size(); ++i) {
		std::cout << " enemy " << i << " ,HP= " << hpData[i]
			  << std::endl;
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
			const iow::PackedVector<Speed> &speedPackedVector,
			const size_t playerIndex, float &playerDeltaTime)
{
	const auto &speedPackedIndicies =
		speedPackedVector.get_packed_indicies();
	const auto &speedPackedData = speedPackedVector.get_packed_data();

	if (speedPackedIndicies.size() != speedPackedData.size())
		Logger::logMessage(
			"ERROR in update position from speed. Velocity packed data is not the same size");
	for (size_t i = 0; i < speedPackedData.size(); ++i) {
		if (speedPackedIndicies[i] == playerIndex) {

			positionPackedVector[speedPackedIndicies[i]] +=
				speedPackedData[i] * playerDeltaTime;
		} else {
			positionPackedVector[speedPackedIndicies[i]] +=
				speedPackedData[i] * dt;
		}
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
//    Pathfinding
// -----------------------------------------

static inline std::vector<iow::Position>
pathfindToPositionFromPositionWithTileMap(
	iow::TileMapPathfinding::Graph const &graph, // graph
	iow::TileMap const &tilemap, // tile map -- needed to find the proper
				     // world coordinates
	iow::Position const &start, //  normally enemy
	iow::Position const &dest   // player
)
{

	iow::GraphCoord const startCoord =
		tilemap.getTileIndex(tilemap.getTileCoordFromWorldCoord(start));
	iow::GraphCoord const destCoord =
		tilemap.getTileIndex(tilemap.getTileCoordFromWorldCoord(dest));

	std::vector<iow::Position> path = iow::Pathfinding::ShortestPath<
		iow::TileCoordi, iow::TileMapPathfinding::MAX_TILE_MAP_EDGES,
		iow::Position>::
		dijkstrasPath(
			graph, startCoord, destCoord,
			[tilemap](iow::TileCoordi const a) -> iow::Position {
				return iow::Position(
					tilemap.getTileWorldCoord(a).x
						+ (tilemap.getTileSize().x * 1
						   / 4),
					tilemap.getTileWorldCoord(a).y
						+ (tilemap.getTileSize().y * 1
						   / 4)

				);
			}

		);

	if (path.size() == 0) {
		path.push_back(dest);
		return path;
	}
	// path.back() = dest;
	// path.front() = start;


	std::cout << "---" << std::endl;
	for (auto const &i : path) {
		std::cout << i.x << ", " << i.y << std::endl;
	}

	return path;
}


static inline void
pathfindTo(iow::PackedVector<bool> const &startSet,
	   iow::PackedVector<iow::Position> &pathsPackedVec,
	   iow::PackedVector<iow::Position> const &posPackedVec,
	   iow::Position const dest,
	   iow::TileMapPathfinding::Graph const &graph, // graph
	   iow::TileMap const &tilemap // tile map -- needed to find the proper
				       // world coordinates
)
{
	std::vector<size_t> const &setpackedindices =
		startSet.get_packed_indicies();

	for (size_t const i : setpackedindices) {
		auto const start = posPackedVec[i];

		iow::GraphCoord const startCoord = tilemap.getTileIndex(
			tilemap.getTileCoordFromWorldCoord(start));
		if (!iow::TileMapPathfinding::isGraphCoordWall(graph,
							       startCoord)) {
			pathsPackedVec[i] =
				pathfindToPositionFromPositionWithTileMap(
					graph, tilemap, start, dest)[1];
		}
	}
}


// -----------------------------------------
//    Render systems
// -----------------------------------------
static inline void renderEntityToSFMLRenderBuffer(sf::RenderWindow &window,
						  const sf::Sprite &sprite,
						  const iow::Camera &camera)
{
	/* sf::Vector2f lengthOffset = sf::Vector2f(0, 0); */
	// uncommenting this code block sets it so that it will rende
	// rnicelyin the center of the screen, howevre it will not play
	// nicely with hte collision system
	// TODO -- not exactly too sure how to go about fixing this....
	/* sf::Vector2f lengthOffset = sf::Vector2f( */
	/* 	-static_cast<float>(sprite.getTextureRect().width)
	 * / 2.f, */
	/* 	static_cast<float>(sprite.getTextureRect().height)
	 * / 2.f); */

	sf::Vector2f npos;

	npos = (sprite.getPosition() - (camera.position));


	npos.x *= camera.scale.x;
	npos.y *= camera.scale.y;

	npos.x += (camera.windowsize.x * std::pow(camera.scale.x, -1)) * 0.5f;
	npos.y += (camera.windowsize.y * std::pow(camera.scale.y, -1)) * 0.5f;

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
