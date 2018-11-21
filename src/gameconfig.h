#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "tilemap.h"

namespace iow
{
struct Entity {
	sf::Vector2f size;
	sf::Vector2f spawnPosition;
	sf::Sprite sprite;
	sf::Texture texture;
};

struct PlayerConfig : public Entity {
	float hp;
	float bulletInterval;
	sf::Vector2f speed;
};

struct DestroyableWallConfig : public Entity {
};

struct EnemyConfig : public Entity {
	float hp;
	sf::Vector2f speed;
};

struct ScaryEnemyConfig : public Entity {
	float bulletInterval;
	float bulletSpeed;
};

struct CameraConfig {
	sf::Vector2f topLeftPosition;
	sf::Vector2f botRightPosition;
};
struct BulletConfig {
	sf::Sprite sprite;
	sf::Texture texture;
	float bulletVelocity;
};

using TileMapConfig = iow::TileMap;


} // namespace iow
