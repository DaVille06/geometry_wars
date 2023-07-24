#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		// if not paused do some things
		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
		}

		sUserInput();
		sRender();

		// increment the current frame
		// may need to be moved when pause implemented
		m_currentFrame++;
	}
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string configCode;

	while (fin >> configCode)
	{
		if (configCode == "Window")
		{
			readWindowConfig(fin);
		}
		else if (configCode == "Font")
		{
			readFontConfig(fin);
		}
		else if (configCode == "Player")
		{
			readPlayerConfig(fin);
		}
		else if (configCode == "Enemy")
		{
			readEnemyConfig(fin);
		}
		else if (configCode == "Bullet")
		{
			readBulletConfig(fin);
		}
		else
		{
			std::cout << "Unknown entry in config file!";
		}
	}

	spawnPlayer();
}

void Game::setPaused(bool paused) 
{
	m_paused = paused;
}

// ***** SYSTEMS *****
void Game::sMovement()
{
	// todo: handle movement for all ENTITIES - NOT JUST PLAYER
	
	// ENEMY MOVEMENT
	for (auto enemy : m_entities.getEntities("enemy"))
	{
		if ((enemy->cTransform->pos.x + enemy->cShape->circle.getRadius() >= m_window.getSize().x) ||
			(enemy->cTransform->pos.x - enemy->cShape->circle.getRadius() <= 0))
			enemy->cTransform->velocity.x *= -1;

		if ((enemy->cTransform->pos.y + enemy->cShape->circle.getRadius() >= m_window.getSize().y) ||
			(enemy->cTransform->pos.y - enemy->cShape->circle.getRadius() <= 0))
			enemy->cTransform->velocity.y *= -1;

		enemy->cTransform->pos.x += enemy->cTransform->velocity.x;
		enemy->cTransform->pos.y += enemy->cTransform->velocity.y;
	}

	// PLAYER MOVEMENT
	m_player->cTransform->velocity = { 0,0 };

	if (m_player->cInput->up &&
		(m_player->cTransform->pos.y - m_playerConfig.CR >= 0))
	{
		m_player->cTransform->velocity.y = -m_playerConfig.S;
	}
	if (m_player->cInput->left &&
		(m_player->cTransform->pos.x - m_playerConfig.CR >= 0))
	{
		m_player->cTransform->velocity.x = -m_playerConfig.S;
	}
	if (m_player->cInput->down &&
		(m_player->cTransform->pos.y + m_playerConfig.CR <= m_window.getSize().y))
	{
		m_player->cTransform->velocity.y = m_playerConfig.S;
	}
	if (m_player->cInput->right &&
		(m_player->cTransform->pos.x + m_playerConfig.CR <= m_window.getSize().x))
	{
		m_player->cTransform->velocity.x = m_playerConfig.S;
	}

	m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sUserInput()
{
	// todo: handle mouse clicks

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_running = false;

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W Key Pressed\n";
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				std::cout << "A Key Pressed\n";
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				std::cout << "S Key Pressed\n";
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				std::cout << "D Key Pressed\n";
				m_player->cInput->right = true;
				break;
			case sf::Keyboard::P:
				std::cout << "P Key Pressed\n";
				setPaused(!m_paused);
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W Key Released\n";
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				std::cout << "A Key Released\n";
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				std::cout << "S Key Released\n";
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				std::cout << "D Key Released\n";
				m_player->cInput->right = false;
				break;
			case sf::Keyboard::R:
				std::cout << "R Key Released\n";
				resetGame();
			default:
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				//spawnBullet();
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

	for (auto e : m_entities.getEntities())
	{
		// set the position of the shape based on the entitys transform->pos
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		// set the rotation of the shape based on the entitys transform->angle
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		m_window.draw(e->cShape->circle);
	}

	m_window.display();
}

void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
		spawnEnemy();
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
	auto entity = m_entities.addEntity("player");

	float midx = m_window.getSize().x / 2.0f;
	float midy = m_window.getSize().y / 2.0f;
	entity->cTransform = std::make_shared<CTransform>(
		Vec2(midx, midy), Vec2(0.0f, 0.0f), 0.0f);

	entity->cShape = std::make_shared<CShape>(
		m_playerConfig.SR, m_playerConfig.V, 
		sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), 
		sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), 
		m_playerConfig.OT);

	entity->cInput = std::make_shared<CInput>();
	entity->cScore = std::make_shared<CScore>(0);
	entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

	m_player = entity;
}

// spawn enemy at a random position
void Game::spawnEnemy()
{
	// todo: the enemy must be spawned completely within the bounds of the window
	auto entity = m_entities.addEntity("enemy");

	// not correct
	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;

	// random example 
	srand(time(NULL));
	
	// random range example
	// diff = 1 + max - min
	// r = rand() % diff
	//	r = random value from [0, diff - 1]
	// r = r + min;
	// r = (rand() % (1 + max - min)) + min;
	
	// random vertices
	int randVertices = (rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN)) + m_enemyConfig.VMIN;
	float randSpeed = (rand() % (int)(1 + m_enemyConfig.SMAX - m_enemyConfig.SMIN)) + m_enemyConfig.SMIN;

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey),
		Vec2(randSpeed, randSpeed), 0.0f);

	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, randVertices, sf::Color(0, 0, 0), 
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

	entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

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

void Game::resetGame()
{
	// clear score
	// set all enemies to dead
	m_player->cScore->score = 0;

	for (auto& entity : m_entities.getEntities("enemy"))
	{
		entity->destroy();
	}
}

// ***** READ CONFIGS *****
void Game::readWindowConfig(std::ifstream& fin)
{
	// W H FL FS
	int width, height, frameRateLimit;
	bool fullScreen;
	fin >>
		width >>
		height >>
		frameRateLimit >>
		fullScreen;
	m_window.create(sf::VideoMode(width, height), "Geometry Wars!");
	m_window.setFramerateLimit(frameRateLimit);
}

void Game::readFontConfig(std::ifstream& fin)
{
	// F S R G B
	std::string fontFileName;
	int fontSize, rFontColor, gFontColor, bFontColor;
	fin >> fontFileName;

	if (!m_font.loadFromFile(fontFileName))
	{
		perror("There was a problem loading the specified font file. Please check config and try again...");
	}

	fin >>
		fontSize >>
		rFontColor >>
		gFontColor >>
		bFontColor;
	m_text.setFont(m_font);
	m_text.setCharacterSize(fontSize);
	m_text.setFillColor(sf::Color(rFontColor, gFontColor, bFontColor));
}

void Game::readPlayerConfig(std::ifstream& fin)
{
	// SR CR S FR FG FB OR OG OB OT V
	fin >>
		m_playerConfig.SR >>
		m_playerConfig.CR >>
		m_playerConfig.S >>
		m_playerConfig.FR >>
		m_playerConfig.FG >>
		m_playerConfig.FB >>
		m_playerConfig.OR >>
		m_playerConfig.OG >>
		m_playerConfig.OB >>
		m_playerConfig.OT >>
		m_playerConfig.V;
}

void Game::readEnemyConfig(std::ifstream& fin)
{
	// SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI
	fin >>
		m_enemyConfig.SR >>
		m_enemyConfig.CR >>
		m_enemyConfig.SMIN >>
		m_enemyConfig.SMAX >>
		m_enemyConfig.OR >>
		m_enemyConfig.OG >>
		m_enemyConfig.OB >>
		m_enemyConfig.OT >>
		m_enemyConfig.VMIN >>
		m_enemyConfig.VMAX >>
		m_enemyConfig.L >>
		m_enemyConfig.SI;
}

void Game::readBulletConfig(std::ifstream& fin)
{
	// SR CR S FR FG FB OR OG OB OT V L
	fin >>
		m_bulletConfig.SR >>
		m_bulletConfig.CR >>
		m_bulletConfig.S >>
		m_bulletConfig.FR >>
		m_bulletConfig.FG >>
		m_bulletConfig.FB >>
		m_bulletConfig.OR >>
		m_bulletConfig.OG >>
		m_bulletConfig.OB >>
		m_bulletConfig.OT >>
		m_bulletConfig.V >>
		m_bulletConfig.L;
}