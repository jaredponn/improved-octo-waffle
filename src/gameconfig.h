#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

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
	float hp;
	float bulletInterval;
	float speed;
};

struct DestroyableWallConfig : public Entity {
};

struct EnemyConfig : public Entity {
	float hp;
	float speed;
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
