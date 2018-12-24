#include "resourcemanager.h"
#include "defaulttilemap.h"
#include "logger.h"

namespace iow
{


iow::ResourceManager::ResourceManager()
{
	/* keybind */
	m_key_binds.resize(iow::MAX_NUMBER_KEYS,
			   {iow::KeyState::INVALID_STATE,
			    iow ::PlayerGameEvents::NO_ACTION});
	m_key_binds[sf::Keyboard::W] = {iow::KeyState::DOWN,
					iow::PlayerGameEvents::MOVE_PLAYER_UP};
	m_key_binds[sf::Keyboard::A] = {
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_LEFT};
	m_key_binds[sf::Keyboard::S] = {
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_DOWN};
	m_key_binds[sf::Keyboard::D] = {
		iow::KeyState::DOWN, iow::PlayerGameEvents::MOVE_PLAYER_RIGHT};
	m_key_binds[sf::Keyboard::Space] = {
		iow::KeyState::PRESSED, iow::PlayerGameEvents::PLAYER_SHOOT};

	/* key chords */
	m_key_chords.push_back(std::make_pair(
		std::vector<iow::SFKeyAndKeyStatePair>{
			std::make_pair(sf::Keyboard::W, iow::KeyState::DOWN),
			std::make_pair(sf::Keyboard::D, iow::KeyState::DOWN)},
		iow::PlayerGameEvents::MOVE_PLAYER_UP_RIGHT));

	m_key_chords.push_back(std::make_pair(
		std::vector<iow::SFKeyAndKeyStatePair>{
			std::make_pair(sf::Keyboard::W, iow::KeyState::DOWN),
			std::make_pair(sf::Keyboard::A, iow::KeyState::DOWN)},
		iow::PlayerGameEvents::MOVE_PLAYER_UP_LEFT));

	m_key_chords.push_back(std::make_pair(
		std::vector<iow::SFKeyAndKeyStatePair>{
			std::make_pair(sf::Keyboard::S, iow::KeyState::DOWN),
			std::make_pair(sf::Keyboard::D, iow::KeyState::DOWN)},
		iow::PlayerGameEvents::MOVE_PLAYER_DOWN_RIGHT));

	m_key_chords.push_back(std::make_pair(
		std::vector<iow::SFKeyAndKeyStatePair>{
			std::make_pair(sf::Keyboard::A, iow::KeyState::DOWN),
			std::make_pair(sf::Keyboard::S, iow::KeyState::DOWN)},
		iow::PlayerGameEvents::MOVE_PLAYER_DOWN_LEFT));

	/*textures*/
	m_textures.loadTextureFromFile("player", "../resources/muted.png");
	m_textures.loadTextureFromFile("enemy", "../resources/muted.png");
	m_textures.loadTextureFromFile("ground", "../resources/bg.png");
	m_textures.loadTextureFromFile("staticwall", "../resources/wall.png");
	m_textures.loadTextureFromFile("bullet", "../resources/muted.png");

	/* player stuff */
	m_player_config.collisionBox = sf::RectangleShape(sf::Vector2f(32, 32));
	m_player_config.bulletInterval = 10;
	m_player_config.hp = 10;
	m_player_config.spawnPosition = sf::Vector2f(250, 250);
	m_player_config.size = sf::Vector2f(32, 32);
	m_player_config.speed = 0.25;

	m_player_config.sprite.setTexture(m_textures.getTexture("player"));
	m_player_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_player_config.sprite.setPosition(0, 0);

	/* enemy stuff */
	m_enemy_config.hp = 100;
	m_enemy_config.speed = 0.0001;
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
	m_camera_config.scale = sf::Vector2f(1.0f, -1.0f);

	/* Tile map */
	// must be set before everything else
	m_tile_map_config.setTileSize(100, 100);

	/* Indiviudal tile configs  */ // must be declared before
				       // loading the tile maps
	auto groundConf = std::make_optional<TileConfig>(
		m_textures.getTexture("ground"), std::nullopt, std::nullopt);
	m_tile_map_config.setTileConfig(0, std::move(groundConf));

	auto colLayer = std::make_optional<iow::TileCollisionLayer>(
		sf::Vector2f(100, 100));
	auto staticWallConf = std::make_optional<TileConfig>(
		m_textures.getTexture("staticwall"), colLayer, std::nullopt);

	m_tile_map_config.setTileConfig(1, std::move(staticWallConf));

	// loading the tile maps
	m_tile_map_config.loadTileMap(iow::DEFAULT_TILE_MAP);

	/* bullet configs */
	m_bullet_config.speed = 2.f;

	m_bullet_config.sprite.setTexture(m_textures.getTexture("bullet"));
	m_bullet_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_bullet_config.sprite.setColor(sf::Color::Yellow);
}

} // namespace iow
