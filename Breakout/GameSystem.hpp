#pragma once
#include "EntityManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

struct windowConfig { int width, height, fps; };


class GameSystem {
	std::shared_ptr<EntityManager> m_entityManager;
	sf::RenderWindow window;
	bool m_pause = false;
public:
	GameSystem();
	void loadConfig();
	void applyConfig();
	void resetGame();
	void run();
	void handleUserInput();
	void transform();
	void collisionCheck();
	void render();

};