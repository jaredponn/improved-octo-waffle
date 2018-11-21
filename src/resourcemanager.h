#pragma once


#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "gameconfig.h"
#include "camera.h"
#include "input.h"

namespace iow
{
using KeyBind = std::pair<iow::KeyState, iow::PlayerGameEvents>;

class ResourceManager
{
    public:
	ResourceManager();

	// keyboard config
	std::vector<KeyBind> m_key_binds;

	// states
	iow::PlayerConfig m_player_config;
	iow::EnemyConfig m_enemy_config;
	iow::ScaryEnemyConfig m_scary_enemy_config;
	iow::Camera m_camera_config;
	iow::BulletConfig m_bullet_config;
	std::vector<iow::DestroyableWallConfig> m_destroyable_wall_configs;
	iow::BulletConfig m_bullet_config;

	iow::TileMapConfig m_tile_map_config;
	std::vector<TileConfig> m_tile_configs;
};
} // namespace iow
