#include "GameSystem.hpp"
#include <iostream>
#include <format>
#include <random>
#include "Profiler.hpp"
GameSystem::GameSystem()
    : m_entityManager(std::shared_ptr<EntityManager>(new EntityManager()))
    , window(sf::RenderWindow(sf::VideoMode(config.width, config.height), "Breakout"))
{
    window.setFramerateLimit(config.fps);
}

void GameSystem::resetGame() {
    PROFILE_FUNCTION();
    m_entityManager->clear();
    m_score = 0;
    unsigned col = 15, row = 20;
    float blockProportionH = 0.6f, blockProportionW = 0.95f;
    float width = (config.width * (blockProportionW-0.1f))/ col;
    float height = (config.height * (blockProportionH-0.1f))/ row;
    float wDiff = (config.width * (1.0f - blockProportionW) + width) / 2.0f;
    float hDiff = height;
    float hStart = config.height * (1.f - blockProportionH) / 4.f;
    unsigned colorAdder = 255 / row;
    for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < row; j++) {
            spawnBlock((config.width * blockProportionW / col)*i + wDiff,
                (config.height * blockProportionH / (row)) * j + hDiff + hStart,
                width, height, true, sf::Color(colorAdder * j, 255 - colorAdder * j, 255));
        }
    }
    float playerX = config.width / 2.0f, playerY = config.height * 0.9f;
    //spawn player & ball
    spawnPlayer(playerX, playerY, width*2.0f, height/2.f);
    spawnBall(playerX, (playerY + config.height * blockProportionH) / 2.0f, 10.f);
    //spawn walls
    spawnInvisibleWall(-50.f, config.height / 2.f, 100.f, config.height); // left wall
    spawnInvisibleWall(config.width + 50.f, config.height / 2.f, 100.f, config.height); // right wall
    spawnInvisibleWall(config.width / 2.f, -50.f, config.width + 200.f, 100.f); // upper wall

}

void GameSystem::run(){
    PROFILE_FUNCTION();
    resetGame();
    sf::Clock clock;
    while (window.isOpen())
    {   
        PROFILE_SCOPE("Frame");
        float deltaTime = clock.restart().asSeconds() * 60.f;
        if (!m_pause) {
            m_entityManager->update();
            handleUserInput();
            transform(deltaTime);
            checkPhysics();
            checkGameLogic(deltaTime);
        }
        else {
            m_entityManager->update();
            handleUserInput();
        }
        render();
        
    }
}

void GameSystem::handleUserInput(){
    PROFILE_FUNCTION();
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                m_pause = !m_pause;
            }
            if (event.key.code == sf::Keyboard::R) {
                resetGame();
            }
            auto& playerInputEntities = m_entityManager->getEntities(ComponentType::PLAYER_INPUT);
            if (event.key.code == sf::Keyboard::Left) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingLeft = true;
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingRight = true;
                }
            }
            if (event.key.code == sf::Keyboard::Up) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    if(!component->leftRightMode)
                        component->isMovingUp = true;
                }
            }
            if (event.key.code == sf::Keyboard::Down) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    if (!component->leftRightMode)
                        component->isMovingDown = true;
                }
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            auto& playerInputEntities = m_entityManager->getEntities(ComponentType::PLAYER_INPUT);
            if (event.key.code == sf::Keyboard::Left) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingLeft = false;
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingRight = false;
                }
            }
            if (event.key.code == sf::Keyboard::Up) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    if (!component->leftRightMode)
                        component->isMovingUp = false;
                }
            }
            if (event.key.code == sf::Keyboard::Down) {
                for (auto& entity : playerInputEntities) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    if (!component->leftRightMode)
                        component->isMovingDown = false;
                }
            }
        }
    }
}
void GameSystem::transform(float timeStep){
    PROFILE_FUNCTION();
    for (auto& entity : m_entityManager->getEntities(ComponentType::PLAYER_INPUT)) {
        auto PIComponent = entity->getComponent<PlayerInputComponent>();
        auto TComponent = entity->getComponent<TransformationComponent>();
        TComponent->velocity.set(0, 0);

        if (PIComponent->isMovingLeft) {
            TComponent->velocity.x = -config.playerSpeed;
        }
        if (PIComponent->isMovingRight) {
            TComponent->velocity.x = config.playerSpeed;
        }
        if (PIComponent->isMovingUp) {
            TComponent->velocity.y = config.playerSpeed;
        }
        if (PIComponent->isMovingDown) {
            TComponent->velocity.y = -config.playerSpeed;
        }
    }
    // apply acceleration and velocity
    for (auto& entity : m_entityManager->getEntities(ComponentType::TRANSFORMATION)) {
        auto component = entity->getComponent<TransformationComponent>();
        component->velocity += component->acceleration * timeStep;
        component->position += component->velocity * timeStep;
    }

}

void GameSystem::render(){
    {
        PROFILE_FUNCTION();
        window.clear();
        for (auto& entity : m_entityManager->getEntities(ComponentType::SHAPE_RENDER)) {
            auto shape = entity->getComponent<ShapeRenderComponent>();
            const auto& position = entity->getComponent<TransformationComponent>()->position;
            if (shape->getShapeType() == ShapeType::RECTANGLE) {
                auto rect = shape->getShape<sf::RectangleShape>();
                rect->setPosition(position.x, position.y);
                window.draw(*rect);
            }
            else if (shape->getShapeType() == ShapeType::CIRCLE) {
                auto circle = shape->getShape<sf::CircleShape>();
                circle->setPosition(position.x, position.y);
                window.draw(*circle);
            }
        }
    }
    PROFILE_SCOPE("Sleeping");
    window.display();
}


bool GameSystem::checkCollision(const std::shared_ptr<CollisionComponent>& collisionA,
    const std::shared_ptr<CollisionComponent>& collisionB,
    const std::shared_ptr<TransformationComponent>& transformA,
    const std::shared_ptr<TransformationComponent>& transformB) {
    const Vec2& posA = transformA->position;
    const Vec2& posB = transformB->position;

    //circle to circle or rect to rect
    if (collisionA->type == collisionB->type) {
        // rect to rect, AABB
        if (collisionA->type == CollisionBoxType::RECTANGLE) {
            Vec2 delta = posA.delta(posB);
            float overlapX = collisionA->halfWidth + collisionB->halfWidth - delta.x;
            float overlapY = collisionA->halfHeight + collisionB->halfHeight - delta.y;
            if (overlapX > 0 && overlapY > 0) {
                return true;
            }
            return false;
        }
        // circle to circle
        else {
            float radiusA = collisionA->halfWidth;
            float radiusB = collisionB->halfWidth;
            float dist = posA.dist(posB);
            return (radiusA + radiusB) > dist;
        }
    }
    // circle to rect
    else {
        Vec2 delta = posA.delta(posB);
        float halfWidth = 0, halfHeight = 0;
        float radius = 0;
        if (collisionA->type == CollisionBoxType::RECTANGLE) {
            halfWidth = collisionA->halfWidth;
            halfHeight = collisionA->halfHeight;
            radius = collisionB->halfWidth;
        }
        else {
            halfWidth = collisionB->halfWidth;
            halfHeight = collisionB->halfHeight;
            radius = collisionA->halfWidth;
        }
        // outer space
        if (delta.x > halfWidth + radius) return false;
        if (delta.y > halfHeight + radius) return false;
        // inner space
        if (delta.x < halfWidth) return true;
        if (delta.y < halfHeight) return true;
        // corner case
        float cornerDist = (delta.x - halfWidth) * (delta.x - halfWidth)
            + (delta.y - halfHeight) * (delta.y - halfHeight);
        return cornerDist < radius * radius;
    }
}

void GameSystem::resolveCollisionCircleRect(std::shared_ptr<CollisionComponent>& collisionCircle,
    std::shared_ptr<CollisionComponent>& collisionRect,
    std::shared_ptr<TransformationComponent>& transformCircle,
    std::shared_ptr<TransformationComponent>& transformRect) {
    // only circle moves
    if (!collisionCircle->doNotMoveWhenCollide) {
        if (collisionCircle->bouncible) {
            Vec2& posC = transformCircle->position;
            Vec2& velC = transformCircle->velocity;
            Vec2& posR = transformRect->position;
            Vec2 delta = posC.delta(posR);
            float halfWidth = collisionRect->halfWidth, halfHeight = collisionRect->halfHeight;
            float radius = collisionCircle->halfWidth;
            // inner space
            if (delta.x < halfWidth) {
                if (posC.y > posR.y) {
                    posC.y += halfHeight + radius - delta.y;
                }
                else {
                    posC.y -= halfHeight + radius - delta.y;
                }
                velC.y = -velC.y;
                return;
            }
            if (delta.y < halfHeight) {
                if (posC.x > posR.x) {
                    posC.x += halfWidth + radius - delta.x;
                }
                else {
                    posC.x -= halfWidth + radius - delta.x;
                }
                velC.x = -velC.x;
                return;
            }
            //TODO
            // corner case
            Vec2 corner({ halfWidth, halfHeight });
            Vec2 cornerToCircleVec = delta - corner;
            float distToMove = radius - cornerToCircleVec.length();
            cornerToCircleVec.resize(distToMove);
            if (posC.x < posR.x) {
                cornerToCircleVec.x = -cornerToCircleVec.x;
            }
            if (posC.y < posR.y) {
                cornerToCircleVec.y = -cornerToCircleVec.y;
            }
            posC += cornerToCircleVec;
            velC = cornerToCircleVec.resize(velC.length());
            return;

        }
    }
    else {
        //TODO
    }

}

void GameSystem::resolveCollisionAABB(std::shared_ptr<CollisionComponent>& collisionA,
    std::shared_ptr<CollisionComponent>& collisionB,
    std::shared_ptr<TransformationComponent>& transformA,
    std::shared_ptr<TransformationComponent>& transformB) {
    if (!collisionA->doNotMoveWhenCollide) {
        if (collisionA->bouncible) {
            // TODO
            transformA->velocity.negate();
            transformA->acceleration.negate();
        }
        else {
            if (!collisionB->breakable) {
                Vec2& posA = transformA->position;
                Vec2& posB = transformB->position;
                Vec2 delta = posA.delta(posB);
                float overlapX = collisionA->halfWidth + collisionB->halfWidth - delta.x;
                float overlapY = collisionA->halfHeight + collisionB->halfHeight - delta.y;
                if (overlapX < overlapY) {
                    if (posA.x > posB.x) {
                        posA.x += overlapX;
                    }
                    else {
                        posA.x -= overlapX;
                    }
                    transformA->velocity.x = 0.f;
                    transformA->acceleration.x = 0.f;
                }
                else {
                    if (overlapY > 0) {
                        if (posA.y > posB.y) {
                            posA.y += overlapY;
                        }
                        else {
                            posA.y -= overlapY;
                        }
                    }
                    transformA->velocity.y = 0.f;
                    transformA->acceleration.y = 0.f;
                }
            }
        }
    }
}

void GameSystem::resolveCollision(std::shared_ptr<CollisionComponent>& collisionA,
    std::shared_ptr<CollisionComponent>& collisionB,
    std::shared_ptr<TransformationComponent>& transformA,
    std::shared_ptr<TransformationComponent>& transformB) {
    // TODO
    
    //circle to circle or rect to rect
    if (collisionA->type == collisionB->type) {
        // rect to rect, AABB
        if (collisionA->type == CollisionBoxType::RECTANGLE) {
            // changes A
            resolveCollisionAABB(collisionA, collisionB, transformA, transformB);
            // changes B
            resolveCollisionAABB(collisionB, collisionA, transformB, transformA);
        }
        // circle to circle
        else {
            // TODO
            // doesn't need to implement yet.
        }
    }
    // circle to rect
    else {
        // TODO
        if (collisionA->type == CollisionBoxType::RECTANGLE) {
            resolveCollisionCircleRect(collisionB, collisionA, transformB, transformA);
        }
        else {
            resolveCollisionCircleRect(collisionA, collisionB, transformA, transformB);
        }
        
    }

}
void GameSystem::checkPhysics() {
    PROFILE_FUNCTION();
    // TODO
    auto& entityList = m_entityManager->getEntities(ComponentType::COLLISION);
    size_t entityListSize = entityList.size();
    for (size_t i = 0; i < entityListSize; ++i) {
        for (size_t j = i+1; j < entityListSize; ++j) {
            auto& entityA = entityList[i];
            auto& entityB = entityList[j];
            auto collisionA = entityA->getComponent<CollisionComponent>();
            auto collisionB = entityB->getComponent<CollisionComponent>();
            auto transformA = entityA->getComponent<TransformationComponent>();
            auto transformB = entityB->getComponent<TransformationComponent>();
            if (checkCollision(collisionA, collisionB, transformA, transformB)) {
                if (collisionA->breakable) {
                    entityA->destroy();
                    m_score += 100;
                }
                if (collisionB->breakable) {
                    entityB->destroy();
                    m_score += 100;
                }
                resolveCollision(collisionA, collisionB, transformA, transformB);
            }
        }
    }
}
void GameSystem::checkGameLogic(float deltaTime) {
    PROFILE_FUNCTION();
    auto& entityList = m_entityManager->getEntities(ComponentType::SHAPE_RENDER);
    for (const auto& entity : entityList) {
        if (entity->getComponent<ShapeRenderComponent>()->getShapeType() == ShapeType::CIRCLE) {
            const auto& pos = entity->getComponent<TransformationComponent>()->position;
            if (pos.y > config.height + 50) {
                resetGame();
                break;
            }
            auto& vel = entity->getComponent<TransformationComponent>()->velocity;
            vel.resize(std::min(vel.length() + config.ballSpeedIncrement * deltaTime, config.maxBallSpeed));
        }
    }

}

void GameSystem::spawnBlock(float x, float y, float width, float height, bool breakable, sf::Color color) {
    auto entity = m_entityManager->addEntity();
    auto shapeC = entity->addComponent<ShapeRenderComponent>();
    shapeC->toRectangle(width, height);
    shapeC->setColor(color);
    auto collisionC = entity->addComponent<CollisionComponent>();
    collisionC->breakable = breakable;
    collisionC->halfHeight = height /2.f;
    collisionC->halfWidth = width / 2.f;
    collisionC->doNotMoveWhenCollide = true;
    auto transformC = entity->addComponent<TransformationComponent>();
    transformC->position.set(x, y);
    transformC->velocity.set(0.0f, 0.0f);
}
void GameSystem::spawnPlayer(float x, float y, float width, float height) {
    auto entity = m_entityManager->addEntity();
    auto inputC = entity->addComponent<PlayerInputComponent>();
    inputC->leftRightMode = true;
    auto shapeC = entity->addComponent<ShapeRenderComponent>();
    shapeC->toRectangle(width, height);
    shapeC->setColor(sf::Color(200, 200, 200));
    shapeC->setOutlineColor(sf::Color(255, 255, 255));
    auto collisionC = entity->addComponent<CollisionComponent>();
    collisionC->breakable = false;
    collisionC->halfHeight = height / 2.f;
    collisionC->halfWidth = width / 2.f;
    auto transformC = entity->addComponent<TransformationComponent>();
    transformC->position.set(x, y);
}

void GameSystem::spawnBall(float x, float y, float radius) {
    auto entity = m_entityManager->addEntity();
    auto shapeC = entity->addComponent<ShapeRenderComponent>();
    shapeC->toCircle(radius);
    shapeC->setColor(sf::Color::White);
    auto collisionC = entity->addComponent<CollisionComponent>();
    collisionC->breakable = false;
    collisionC->bouncible = true;
    collisionC->type = CollisionBoxType::CIRCLE;
    collisionC->halfWidth = radius;
    auto transformC = entity->addComponent<TransformationComponent>();
    transformC->position.set(x, y);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
    float randomFloat = distribution(gen);
    transformC->velocity = Vec2(randomFloat, 3.f).resize(config.initialBallSpeed);
}

void GameSystem::spawnInvisibleWall(float x, float y, float width, float height) {
    auto entity = m_entityManager->addEntity();
    auto collisionC = entity->addComponent<CollisionComponent>();
    collisionC->breakable = false;
    collisionC->bouncible = false;
    collisionC->doNotMoveWhenCollide = true;
    collisionC->type = CollisionBoxType::RECTANGLE;
    collisionC->halfHeight = height / 2.f;
    collisionC->halfWidth = width / 2.f;
    auto transformC = entity->addComponent<TransformationComponent>();
    transformC->position.set(x, y);
}