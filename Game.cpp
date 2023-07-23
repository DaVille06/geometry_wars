#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game(const std::string& config)
{
	init(config);
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

void Game::setPaused(bool paused) 
{
	m_paused = paused;
}

// ***** SYSTEMS *****
void Game::sMovement()
{
	// todo: implement all entity movement in this function
	// you should read the m_player->cInput component to determine if the player is moving
	m_player->cTransform->velocity = { 0,0 };

	// implement player movement
	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -5;
	}

	// sample movement speed update
	m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
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
				m_player->cInput->up = true;
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
				m_player->cInput->up = false;
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
	// todo: code which implements enemy spawning should go here

	// use (m_currentFrame - m_lastEnemySpawnTime) to determine
	// how long it has been since the last enemy spawned
	// if curentframe - spawntime is 100 and I want to wait til 200
	// then don't spawn
	//spawnEnemy();
}

void Game::sCollision()
{
	// todo: implement all proper collisions between entities
	// be sure to use the collision radius, NOT the shape radius
}

void Game::sLifespan()
{
	// todo: implement all lifespan functionality
	// for all entities
	// if entity has no lifespan component, skip it
	// if entity has > 0 remaining lifespan, subtract 1
	// if it has lifespan and is alive
	//		scale its alpha chanel properly
	// if it has lifespan and its time is up
	//		destroy the entity
}

// ***** PRIVATE *****
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
		Vec2(midx, midy), Vec2(0.0f, 0.0f), 0.0f);

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
	auto entity = m_entities.addEntity("enemy");

	// give this entity a transform so it spawns at (200, 200) with velocity (1,1) and angle 0
	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

	// the entitys shape will have radius 32, 8 sides, dark grey fill, and red outline of thickness 4
	entity->cShape = std::make_shared<CShape>(16.0f, 8, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

	// record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
	// todo: spawn small enemies at the location of the input enemy entity

	// when we create the smaller enemy, we have to read the values of the original enemy
	// spawn a number of small enemies equal to the vertices of the original enemy
	// set each small enemy to the same color as the original, half the size
	// small enemies are worth double points of the original enemy
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	// todo: implement the spawning of a bullet which travels toward target
	// bullet speed is given as a scalar speed
	// you must set the velocity by using formula in notes
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	// todo: implement your own special weapon
}