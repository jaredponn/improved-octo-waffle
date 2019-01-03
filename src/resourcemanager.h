#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <tuple>
#include <vector>

#include "camera.h"
#include "gameconfig.h"
#include "gameinput.h"
#include "input.h"
#include "texturemanager.h"

namespace iow
{

class ResourceManager
{
    private:
	iow::TextureManager m_textures;

    public:
	ResourceManager();

	// keyboard config
	std::vector<iow::KeyChord> m_key_chords;
	std::vector<iow::SingleKeyBind> m_key_binds;

	// states
	iow::PlayerConfig m_player_config;
	iow::EnemyConfig m_enemy_config;
	iow::ScaryEnemyConfig m_scary_enemy_config;
	iow::Camera m_camera_config;
	iow::BulletConfig m_bullet_config;
	std::vector<iow::DestroyableWallConfig> m_destroyable_wall_configs;

	iow::TileMapConfig m_tile_map_config;
};
} // namespace iow
