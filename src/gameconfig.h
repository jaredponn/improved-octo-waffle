#pragma once
#include <SFML/Graphics.hpp>

namespace iow
{

struct SquishyEntity {
	float hp;
	sf::Vector2f size;
	sf::Vector2f speed;
};

struct PlayerConfig : SquishyEntity {
	float bulletInterval;
	float bulletSpeed;
};

struct DestroyableWallConfig {
	sf::Vector2f size;
	sf::Vector2f position;
};

struct EnemyConfig : SquishyEntity {
};

struct ScaryEnemyConfig : SquishyEntity {
	float bulletInterval;
	float bulletSpeed;
};

struct TileMap {
};

} // namespace iow
