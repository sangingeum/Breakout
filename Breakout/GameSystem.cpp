#include "GameSystem.hpp"
#include <iostream>
GameSystem::GameSystem()
    : m_entityManager(std::shared_ptr<EntityManager>(new EntityManager()))
    , window(sf::RenderWindow(sf::VideoMode(1280, 720), "SFML works!"))
{
    window.setFramerateLimit(60);
}

void GameSystem::loadConfig() {

}

void GameSystem::applyConfig() {

}

void GameSystem::run(){
    loadConfig();
    applyConfig();

    auto entity = m_entityManager->addEntity();
    auto shapeComp = entity->addComponent<ShapeRenderComponent>();
    shapeComp->getShape<sf::RectangleShape>()->setFillColor(sf::Color::Green);
    auto TComp = entity->addComponent<TransformationComponent>();
    TComp->velocity.set(1.0f, 1.0f);
  
   
    while (window.isOpen())
    {   
        if (!m_pause) {
            m_entityManager->update();
            handleUserInput();
            transform();
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
        }
        
    }
}
void GameSystem::transform(){
    for (auto entity : m_entityManager->getEntities(ComponentType::TRANSFORMATION)) {
        auto component = entity->getComponent<TransformationComponent>();
        component->velocity += component->acceleration;
        component->position += component->velocity;
    }

}
void GameSystem::collisionCheck(){}
void GameSystem::render(){
    window.clear();
    for (auto entity : m_entityManager->getEntities(ComponentType::SHAPE_RENDER)) {
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