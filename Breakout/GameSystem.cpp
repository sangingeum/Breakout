#include "GameSystem.hpp"
#include <iostream>
GameSystem::GameSystem()
    : m_entityManager(std::shared_ptr<EntityManager>(new EntityManager()))
    , window(sf::RenderWindow(sf::VideoMode(1280, 720), "SFML works!"))
{
    window.setFramerateLimit(m_frameRate);
}

void GameSystem::loadConfig() {

}

void GameSystem::applyConfig() {

}

void GameSystem::resetGame() {
    auto entity = m_entityManager->addEntity();
    auto shapeComp = entity->addComponent<ShapeRenderComponent>();
    shapeComp->getShape<sf::RectangleShape>()->setFillColor(sf::Color::Green);
    auto TComp = entity->addComponent<TransformationComponent>();
    TComp->velocity.set(1.0f, 1.0f);
    auto player = m_entityManager->addEntity();
    player->addComponent<PlayerInputComponent>();
    player->addComponent<TransformationComponent>();
    auto playerShape = player->addComponent<ShapeRenderComponent>();
    playerShape->toCircle(10.f);
    playerShape->getShape<sf::RectangleShape>()->setFillColor(sf::Color::Blue);

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
            TComponent->acceleration.x -= 0.1f * timeStep;
        }
        if (PIComponent->isMovingRight) {
            TComponent->acceleration.x += 0.1f * timeStep;
        }

    }

    for (auto& entity : m_entityManager->getEntities(ComponentType::TRANSFORMATION)) {
        auto component = entity->getComponent<TransformationComponent>();
        component->velocity += component->acceleration * timeStep;
        component->position += component->velocity * timeStep;
    }


}
void GameSystem::collisionCheck(){}
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
