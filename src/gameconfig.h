#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "collision.h"
#include "texturemanager.h"
#include "tilemap.h"

namespace iow
{
struct Entity {
	sf::Vector2f size;
	sf::Vector2f spawnPosition;
	sf::Sprite sprite;
};

// https://natureofcode.com/book/chapter-6-autonomous-agents/
struct SteeringBehaviour {
	sf::Vector2f steeringVelocity;

	sf::Vector2f desiredVelocity; //  = target - location
	float maxSpeed; // normalize desired velocity, then multiply by max
			// speed
};

struct PlayerConfig : public Entity {
	iow::CollisionBox collisionBox;
	float hp;
	float bulletInterval;
	float speed;
};

struct DestroyableWallConfig : public Entity {
};

struct EnemyConfig : public Entity {
	float hp;
	float speed;

	SteeringBehaviour steeringBehaviour;
};

struct ScaryEnemyConfig : public Entity {
	float bulletInterval;
	float bulletSpeed;
};

struct CameraConfig {
	sf::Vector2f topLeftPosition;
	sf::Vector2f botRightPosition;
};

struct BulletConfig : public Entity {
	float speed;
};

using TileMapConfig = iow::TileMap;


} // namespace iow
