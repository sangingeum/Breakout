#include "GameSystem.hpp"
#include <iostream>
GameSystem::GameSystem()
    : m_entityManager(std::shared_ptr<EntityManager>(new EntityManager()))
    , window(sf::RenderWindow(sf::VideoMode(config.width, config.height), "SFML works!"))
{
    window.setFramerateLimit(config.fps);
}

void GameSystem::loadConfig() {

}

void GameSystem::applyConfig() {

}

void GameSystem::resetGame() {
    size_t col = 15, row = 10;
    float blockProportionH = 0.6, blockProportionW = 0.9;
    float width = (config.width * (blockProportionW-0.1))/ col;
    float height = (config.height * (blockProportionH-0.1))/ row;
    float wDiff = (config.width * (1 - blockProportionW) + width) / 2.0f;
    float hDiff = height;
    for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < row; j++) {
            spawnBlock((config.width * blockProportionW / col)*i + wDiff,
                (config.height * blockProportionH / (row)) * j + hDiff,
                width, height, true);
        }
    }
    spawnPlayer(config.width / 2, config.height * 0.9, width*2, height);
}

void GameSystem::run(){
    loadConfig();
    applyConfig();
    resetGame();
    while (window.isOpen())
    {   
        if (!m_pause) {
            m_entityManager->update();
            handleUserInput();
            transform(m_frameDelay);
            collisionCheck();
        }
        else {
            m_entityManager->update();
            handleUserInput();
        }
        render();
        
    }
}

void GameSystem::handleUserInput(){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                m_pause = !m_pause;
            }
            if (event.key.code == sf::Keyboard::Left) {
                for (auto& entity : m_entityManager->getEntities(ComponentType::PLAYER_INPUT)) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingLeft = true;
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                for (auto& entity : m_entityManager->getEntities(ComponentType::PLAYER_INPUT)) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingRight = true;
                }
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Left) {
                for (auto& entity : m_entityManager->getEntities(ComponentType::PLAYER_INPUT)) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingLeft = false;
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                for (auto& entity : m_entityManager->getEntities(ComponentType::PLAYER_INPUT)) {
                    auto component = entity->getComponent<PlayerInputComponent>();
                    component->isMovingRight = false;
                }
            }
        }
    }
}
void GameSystem::transform(float timeStep){
 
    for (auto& entity : m_entityManager->getEntities(ComponentType::PLAYER_INPUT)) {
        auto PIComponent = entity->getComponent<PlayerInputComponent>();
        auto TComponent = entity->getComponent<TransformationComponent>();
        TComponent->acceleration.set(0, 0);
        if (PIComponent->isMovingLeft) {
            TComponent->acceleration.x -= 0.15f * timeStep;
        }
        if (PIComponent->isMovingRight) {
            TComponent->acceleration.x += 0.15f * timeStep;
        }

    }

    for (auto& entity : m_entityManager->getEntities(ComponentType::TRANSFORMATION)) {
        auto component = entity->getComponent<TransformationComponent>();

        component->velocity = component->acceleration * timeStep + (component->velocity * 0.99);
        component->position += component->velocity * timeStep;
    }


}
void GameSystem::collisionCheck(){


}
void GameSystem::render(){
    window.clear();
    for (auto& entity : m_entityManager->getEntities(ComponentType::SHAPE_RENDER)) {
        auto shape = entity->getComponent<ShapeRenderComponent>();
        const auto& position = entity->getComponent<TransformationComponent>()->position;
        if (shape->getShapeType() == ShapeType::RECTANGLE) {
            auto rect = shape->getShape<sf::RectangleShape>();
            rect->setPosition(position.x, position.y);
            window.draw(*rect);
        }
        else if(shape->getShapeType() == ShapeType::CIRCLE) {
            auto circle = shape->getShape<sf::CircleShape>();
            circle->setPosition(position.x, position.y);
            window.draw(*circle);
        }
    }
    window.display();
}


void GameSystem::spawnBlock(float x, float y, float width, float height, bool breakable) {
    auto entity = m_entityManager->addEntity();
    auto shapeC = entity->addComponent<ShapeRenderComponent>();
    shapeC->toRectangle(width, height);
    shapeC->setColor(sf::Color::White);
    auto collisionC = entity->addComponent<CollisionComponent>();
    collisionC->breakable = breakable;
    collisionC->width = width;
    collisionC->height = height;
    auto transformC = entity->addComponent<TransformationComponent>();
    transformC->position.set(x, y);
    transformC->velocity.set(0.0f, 0.0f);
}
void GameSystem::spawnPlayer(float x, float y, float width, float height) {
    auto entity = m_entityManager->addEntity();
    entity->addComponent<PlayerInputComponent>();
    auto shapeC = entity->addComponent<ShapeRenderComponent>();
    shapeC->toRectangle(width, height);
    shapeC->setColor(sf::Color::Green);
    auto collisionC = entity->addComponent<CollisionComponent>();
    collisionC->breakable = false;
    collisionC->width = width;
    collisionC->height = height;
    auto transformC = entity->addComponent<TransformationComponent>();
    transformC->position.set(x, y);
    
    
}