#include <SFML/Graphics.hpp>

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	void init();
	void update();

	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();

private:
	sf::RenderWindow m_window;
	bool m_paused;
	bool m_running;
};

#endif // !GAME_H
