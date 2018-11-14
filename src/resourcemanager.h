#pragma once

#include <vector>
#include "../extern/json.hpp"
#include "gameconfig.h"

namespace iow
{
class ResourceManager
{
    public:
	ResourceManager();

    private:
	iow::PlayerConfig m_player_config;
	iow::EnemyConfig m_enemy_config;
	iow::ScaryEnemyConfig m_scary_enemy_config;
	std::vector<iow::DestroyableWallConfig> m_destroyable_wall_configs;
	iow::TileMap m_tile_map;
};

} // namespace iow
