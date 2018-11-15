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


	// player stuff
	m_player_config.bulletInterval = 10;
	m_player_config.bulletSpeed = 10;
	m_player_config.hp = 10;
	m_player_config.position = sf::Vector2f(250, 250);
	m_player_config.size = sf::Vector2f(100, 100);
	m_player_config.speed = sf::Vector2f(1, 1);

	m_player_config.texture.loadFromFile("../resources/muted.png");
	m_player_config.texture.setSmooth(true);

	m_player_config.sprite.setTexture(m_player_config.texture);
	m_player_config.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_player_config.sprite.setPosition(10, 10);

	/* if (!m_player_config.texture.create(200, 200)) { */
	/* 	Logger::logMessage( */
	/* 		"ERROR in ResourceManager. Failed to load
	 * player_config.texture"); */
	/* } */
}
