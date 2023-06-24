#pragma once
#include "EntityManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class GameSystem {
	std::shared_ptr<EntityManager> m_entityManager;
	sf::RenderWindow window;
public:
	GameSystem(std::shared_ptr<EntityManager> entityManager, unsigned int width, unsigned int height);
	
	void mainLoop();
	void handleUserInput();
	void transform();
	void collisionCheck();
	void render();
};