#pragma once
#include "EntityManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

struct Config { int width = 1280, height = 720, fps = 144; };


class GameSystem {
	std::shared_ptr<EntityManager> m_entityManager;
	Config config;
	sf::RenderWindow window;
	float m_frameDelay = 60.0f / config.fps;
	bool m_pause = false;
	void spawnBlock(float x, float y, float width, float height, bool breakable, sf::Color color);
	void spawnPlayer(float x, float y, float width, float height);
	void spawnBall(float x, float y, float radius);
	void spawnInvisibleWall(float x, float y, float width, float height);
	bool checkCollision(const std::shared_ptr<CollisionComponent>& collisionA,
		const std::shared_ptr<CollisionComponent>& collisionB,
		const std::shared_ptr<TransformationComponent>& transformA,
		const std::shared_ptr<TransformationComponent>& transformB);
	void resolveCollision(std::shared_ptr<CollisionComponent>& collisionA,
		 std::shared_ptr<CollisionComponent>& collisionB,
		 std::shared_ptr<TransformationComponent>& transformA,
		 std::shared_ptr<TransformationComponent>& transformB);
	void resolveCollisionCircleRect(std::shared_ptr<CollisionComponent>& collisionCircle,
		std::shared_ptr<CollisionComponent>& collisionRect,
		std::shared_ptr<TransformationComponent>& transformCircle,
		std::shared_ptr<TransformationComponent>& transformRect);
	void resolveCollisionAABB( std::shared_ptr<CollisionComponent>& collisionA,
		 std::shared_ptr<CollisionComponent>& collisionB,
		 std::shared_ptr<TransformationComponent>& transformA,
		 std::shared_ptr<TransformationComponent>& transformB);
	void loadConfig();
	void applyConfig();
	void resetGame();
	void handleUserInput();
	void transform(float timeStep);
	void checkPhysics();
	void render();
public:
	GameSystem();
	void run();

};