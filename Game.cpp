#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	// read in config file here
	std::ifstream fin(path);
	// use the premade PlayerConfig, EnemyConfig, BulletConfig variables

	// if i know im on player portion
	//fin >> m_playerConfig.SR >> m_playerConfig.CR >> ....

	// set up default window parameters
	// read these from config as well
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run()
{
	// add pause functionality here
	// some systems should function while paused (rendering)
	// some systems shouldn't (movement / input)

	while (m_running)
	{
		m_entities.update();

		// if not paused do some things
		if (!m_paused)
		{

		}

		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();

		// increment the current frame
		// may need to be moved when pause implemented
		m_currentFrame++;
	}
}

void Game::setPaused(bool paused) 
{
	m_paused = paused;
}

// respawn in the middle of the screen
void Game::spawnPlayer()
{
	// todo: finish adding all properties of the player with the correct values from the config

	// we create every entity by calling EntityManager.addEntity(tag)
	// this returns a std::shared_ptr<Entity>, so we use auto to save typing
	auto entity = m_entities.addEntity("player");

	// give this entity a transform so it spawns at (200, 200) with velocity (1, 1) and angle 0
	entity->cTransform = std::make_shared<CTransform>(
		Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	// the entitys shape will have radius 32, 8 sides, dark grey fill, and red outline of thickeness 4
	entity->cShape = std::make_shared<CShape>(
		32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	// add an input component to the player so that we can use inputs
	entity->cInput = std::make_shared <CInput>();

	// since we want this entity to be our player, set our games player variable to be this entity
	// this goes slightly against the entity manager paradigm
	m_player = entity;
}

void Game::spawnEnemy() {}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) {}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos) {}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {}

void Game::sMovement()
{

}

void Game::sUserInput()
{

}

void Game::sRender()
{

}

void Game::sEnemySpawner()
{

}

void Game::sCollision()
{

}

void Game::sLifespan()
{

}