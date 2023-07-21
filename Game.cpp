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
	// whats listed is an example - but needs to be changed

	// we create every entity by calling EntityManager.addEntity(tag)
	// this returns a std::shared_ptr<Entity>, so we use auto to save typing
	auto entity = m_entities.addEntity("player");

	// these values will put player in middle of the screen
	float midx = m_window.getSize().x / 2.0f;
	float midy = m_window.getSize().y / 2.0f;
	entity->cTransform = std::make_shared<CTransform>(
		Vec2(midx, midy), Vec2(1.0f, 1.0f), 0.0f);

	// the entitys shape will have radius 32, 8 sides, dark grey fill, and red outline of thickeness 4
	entity->cShape = std::make_shared<CShape>(
		32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	// add an input component to the player so that we can use inputs
	entity->cInput = std::make_shared <CInput>();

	// since we want this entity to be our player, set our games player variable to be this entity
	// this goes slightly against the entity manager paradigm
	m_player = entity;
}

// spawn enemy at a random position
void Game::spawnEnemy() 
{
	// todo: make sure the enemy is spawned properly with the m_enemyConfig variables
	// the enemy must be spawned completely within the bounds of the window

	// record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

// spawns the small enemies when a big one (input entity entity) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) 
{
	// todo: spawn small enemies at the location of the input enemy entity

	// when we create the smaller enemy, we have to read the values of the original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos) {}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {}

void Game::sMovement()
{

}

void Game::sUserInput()
{
	// todo: handle user input here
	// note that you should only be setting the players input component variables here
	// you should not implement the players movement logic here
	// the movement system will read the variables you set in this function

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// this event triggers when the window is closed
		if (event.type == sf::Event::Closed)
			m_running = false;

		// this event is triggered when a key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W Key Pressed\n";
				// todo: set players input component "up" to true
				break;
			case sf::Keyboard::A:
				std::cout << "A Key Pressed\n";
				break;
			case sf::Keyboard::S:
				std::cout << "S Key Pressed\n";
				break;
			case sf::Keyboard::D:
				std::cout << "D Key Pressed\n";
				break;
			}
		}

		// this event triggers when a key is released
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W Key Released\n";
				// todo: set players input component "up" to false
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				// call spawn bullet here
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				// call spawnSpecialWeapon here
			}
		}
	}
}

void Game::sRender()
{
	m_window.clear();

	// draw all entities
	for (auto e : m_entities.getEntities())
	{
		// set the position of the shape based on the entitys transform->pos
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		// set the rotation of the shape based on the entitys transform->angle
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		// draw the entitys sf::CircleShape
		m_window.draw(e->cShape->circle);
	}

	m_window.display();
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