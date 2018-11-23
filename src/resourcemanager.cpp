#include "resourcemanager.h"
#include "logger.h"
#include "defaulttilemap.h"

namespace iow
{


iow::ResourceManager::ResourceManager()
{
	/* keybaord */
	m_key_binds.resize(iow::MAX_NUMBER_KEYS,
			   std::make_pair(iow::KeyState::INVALID_STATE,
					  iow ::PlayerGameEvents::NO_ACTION));
	m_key_binds[sf::Keyboard::W] = std::make_pair(
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_UP);
	m_key_binds[sf::Keyboard::A] = std::make_pair(
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_LEFT);
	m_key_binds[sf::Keyboard::S] = std::make_pair(
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_DOWN);
	m_key_binds[sf::Keyboard::D] = std::make_pair(
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_RIGHT);
	m_key_binds[sf::Keyboard::Space] = std::make_pair(
		iow::KeyState::PRESSED, iow::PlayerGameEvents::PLAYER_SHOOT);

	/*textures*/
	m_textures.loadTextureFromFile("player", "../resources/muted.png");
	m_textures.loadTextureFromFile("enemy", "../resources/muted.png");
	m_textures.loadTextureFromFile("ground", "../resources/bg.png");
	m_textures.loadTextureFromFile("staticwall", "../resources/wall.png");
	m_textures.loadTextureFromFile("bullet", "../resources/muted.png");


	/* player stuff */
	m_player_config.bulletInterval = 10;
	m_player_config.hp = 10;
	m_player_config.spawnPosition = sf::Vector2f(250, 250);
	m_player_config.size = sf::Vector2f(100, 100);
	m_player_config.speed = sf::Vector2f(1, 1);

	m_player_config.sprite.setTexture(m_textures.getTexture("player"));
	m_player_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_player_config.sprite.setPosition(10, 10);

	/* enemy stuff */
	m_enemy_config.hp = 100;
	m_enemy_config.speed = sf::Vector2f(1, 1);
	m_enemy_config.size = sf::Vector2f(100, 100);

	m_enemy_config.spawnPosition = sf::Vector2f(100, 100);

	m_enemy_config.sprite.setTexture(m_textures.getTexture("enemy"));
	m_enemy_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_enemy_config.sprite.setColor(sf::Color::Red);
	m_enemy_config.sprite.setPosition(10, 10);


	/* if (!m_player_config.texture.create(200, 200)) { */
	/* 	Logger::logMessage( */
	/* 		"ERROR in ResourceManager. Failed to load
	 * player_config.texture"); */
	/* } */

	/* camera */
	m_camera_config.position = sf::Vector2f(0.f, 0.f);
	m_camera_config.scale = sf::Vector2f(1.f, -1.0f);

	/* Tile map */
	m_tile_map_config.setTileSize(
		100,
		100); // must be set before everything else

	/* Indiviudal tile configs  */ // must be declared before loading the
				       // tile maps
	auto groundConf = std::make_unique<TileConfig>(
		TileConfig(m_textures.getTexture("ground")));
	m_tile_map_config.setTileConfig(0, std::move(groundConf));

	auto staticWallConf = std::make_unique<TileConfig>(
		TileConfig(m_textures.getTexture("staticwall")));
	m_tile_map_config.setTileConfig(1, std::move(staticWallConf));

	m_tile_map_config.loadTileMap(
		iow::DEFAULT_TILE_MAP); // loading the tile maps

	/* bullet configs */
	m_bullet_config.bulletVelocity = 2.f;

	m_bullet_config.sprite.setTexture(m_textures.getTexture("bullet"));
	m_bullet_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_bullet_config.sprite.setColor(sf::Color::Yellow);
}

} // namespace iow
