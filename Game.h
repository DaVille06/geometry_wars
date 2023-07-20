#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntityManager.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
public:

	Game(const std::string& config);
	void run();

private:
	sf::RenderWindow m_window;				// the window we will draw to
	EntityManager m_entities;				// vector of entities to maintain
	sf::Font m_font;						// the font we will use to draw
	sf::Text m_text;						// the score text to be drawn to the screen
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score{ 0 };
	int m_currentFrame{ 0 };
	int m_lastEnemySpawnTime{ 0 };
	bool m_paused{ false };					// whether we update game logic
	bool m_running{ true };					// whether the game is running

	std::shared_ptr<Entity> m_player;

	void init(const std::string& path);		// initialize the GameState with a config file path
	void setPaused(bool paused);			// pause the game
	
	void sMovement();						// system: entity position / movement update
	void sUserInput();						// system: user input
	void sLifespan();						// system: lifespan
	void sRender();							// system: render / drawing
	void sEnemySpawner();					// system: spawns enemies
	void sCollision();						// system: collisions

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
};

#endif // !GAME_H
