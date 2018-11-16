#include "resourcemanager.h"
#include "logger.h"

iow::ResourceManager::ResourceManager()
{
	// keybaord
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

	// TODO HAIYANG presseing space shoots
	m_key_binds[sf::Keyboard::Space] = std::make_pair(
		iow::KeyState::PRESSED, iow::PlayerGameEvents::PLAYER_SHOOT);


	// player stuff
	m_player_config.bulletInterval = 10;
	m_player_config.hp = 10;
	m_player_config.spawnPosition = sf::Vector2f(250, 250);
	m_player_config.size = sf::Vector2f(100, 100);
	m_player_config.speed = sf::Vector2f(1, 1);

	m_player_config.texture.loadFromFile("../resources/muted.png");
	m_player_config.texture.setSmooth(true);

	m_player_config.sprite.setTexture(m_player_config.texture);
	m_player_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_player_config.sprite.setPosition(10, 10);

	// enemy stuff
	m_enemy_config.hp = 100;
	m_enemy_config.speed = sf::Vector2f(1, 1);
	m_enemy_config.size = sf::Vector2f(100, 100);

	m_enemy_config.spawnPosition = sf::Vector2f(100, 100);
	m_enemy_config.texture.loadFromFile("../resources/muted.png");
	m_enemy_config.texture.setSmooth(true);

	m_enemy_config.sprite.setTexture(m_player_config.texture);
	m_enemy_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_enemy_config.sprite.setColor(sf::Color::Red);
	m_enemy_config.sprite.setPosition(10, 10);


	/* if (!m_player_config.texture.create(200, 200)) { */
	/* 	Logger::logMessage( */
	/* 		"ERROR in ResourceManager. Failed to load
	 * player_config.texture"); */
	/* } */

	// camera
	m_camera_config.position = sf::Vector2f(0.f, 0.f);
	m_camera_config.scale = sf::Vector2f(1.f, -1.0f);
	// bullet configs
	m_bullet_config.bulletVelocity = 2.f;

	m_bullet_config.texture.loadFromFile("../resources/muted.png");
	m_bullet_config.texture.setSmooth(true);
	m_bullet_config.sprite.setTexture(m_player_config.texture);
	m_bullet_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_bullet_config.sprite.setColor(sf::Color::Yellow);
}
