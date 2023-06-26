#pragma once
#include "EntityManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

struct Config { int width = 1280, height = 720, fps = 60; };


class GameSystem {
	std::shared_ptr<EntityManager> m_entityManager;
	Config config;
	sf::RenderWindow window;
	float m_frameDelay = 60.0f / config.fps;
	bool m_pause = false;
	void spawnBlock(float x, float y, float width, float height, bool breakable);
	void spawnPlayer(float x, float y, float width, float height);
public:
	GameSystem();
	void loadConfig();
	void applyConfig();
	void resetGame();
	void run();
	void handleUserInput();
	void transform(float timeStep);
	void collisionCheck();
	void render();

};