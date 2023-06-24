#include "GameSystem.hpp"

GameSystem::GameSystem(std::shared_ptr<EntityManager> entityManager, unsigned int width, unsigned int height)
    : m_entityManager(entityManager)
    , window(sf::RenderWindow(sf::VideoMode(width, height), "SFML works!"))
{
    window.setFramerateLimit(60);
}

void GameSystem::mainLoop(){
    while (window.isOpen())
    {
        m_entityManager->update();
        handleUserInput();
        transform();
        collisionCheck();
        render();
    }
}

void GameSystem::handleUserInput(){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
void GameSystem::transform(){
    for (auto entity : m_entityManager->getEntities(ComponentType::VELOCITY)) {
        auto component = static_pointer_cast<VelocityComponent>(entity->getComponent(ComponentType::VELOCITY));
        auto& position = static_pointer_cast<PositionComponent>(entity->getComponent(ComponentType::POSITION))->position;
        position.x += component->velocity.x;
        position.y += component->velocity.y;
    }

}
void GameSystem::collisionCheck(){}
void GameSystem::render(){
    window.clear();
    for (auto entity : m_entityManager->getEntities(ComponentType::SHAPE_RENDER)) {
        auto component = static_pointer_cast<ShapeRenderComponent>(entity->getComponent(ComponentType::SHAPE_RENDER));
        const auto& position = static_pointer_cast<PositionComponent>(entity->getComponent(ComponentType::POSITION))->position;
        if (component->getShapeType() == ShapeType::RECTANGLE) {
            auto shape = static_pointer_cast<sf::RectangleShape>(component->getShape());
            shape->setPosition(position.x, position.y);
            window.draw(*shape);
        }
        else if(component->getShapeType() == ShapeType::CIRCLE) {
            auto shape = static_pointer_cast<sf::CircleShape>(component->getShape());
            shape->setPosition(position.x, position.y);
            window.draw(*shape);
        }
    }
    window.display();
}