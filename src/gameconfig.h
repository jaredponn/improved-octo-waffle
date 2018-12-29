#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "collision.h"
#include "steeringbehaviour.h"
#include "texturemanager.h"
#include "tilemap.h"

namespace iow
{
struct Entity {
	sf::Vector2f size;
	sf::Vector2f spawnPosition;
	sf::Sprite sprite;
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

	iow::SteeringBehaviour::SteeringBehaviour steeringBehaviour;
};

struct ScaryEnemyConfig : public Entity {
	float bulletInterval;
	float bulletSpeed;
};

struct CameraConfig {
	sf::Vector2f topLeftPosition;
	sf::Vector2f botRightPosition;
};

/* HAIYANG -> update this so the game config a for a bullet can do collisions */
struct BulletConfig : public Entity {
	iow::CollisionCir collisionCir;
	float speed;
};

using TileMapConfig = iow::TileMap;


} // namespace iow
