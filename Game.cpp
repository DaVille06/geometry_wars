#include "Game.h"
#include <iostream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	// read in config file here
	// use the premade PlayerConfig, EnemyConfig, BulletConfig variables

	// set up default window parameters
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::spawnPlayer()
{

}

void Game::run()
{
	// add pause functionality here
	// some systems should function while paused (rendering)
	// some systems shouldn't (movement / input)

	while (m_running)
	{
		
	}
}

void Game::update()
{

}

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