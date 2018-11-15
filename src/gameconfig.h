#pragma once
#include <SFML/Graphics.hpp>

namespace iow
{
struct Entity {
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
};

struct PlayerConfig : public Entity {
	float hp;
	float bulletInterval;
	float bulletSpeed;
	sf::Vector2f speed;
};

struct DestroyableWallConfig : public Entity {
};

struct EnemyConfig : public Entity {
};

struct ScaryEnemyConfig : public Entity {
	float bulletInterval;
	float bulletSpeed;
};

struct CameraConfig {
	sf::Vector2f topLeftPosition;
	sf::Vector2f botRightPosition;
};

struct TileMap {
};


} // namespace iow
