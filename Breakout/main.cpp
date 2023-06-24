#include <iostream>
#include <format>
#include <SFML/Graphics.hpp>
#include "GameSystem.hpp"

int main()
{   
    auto entityManager = std::make_shared<EntityManager>();
    auto entity = entityManager->addEntity({ ComponentType::POSITION, ComponentType::VELOCITY, ComponentType::SHAPE_RENDER });
    auto shapeComp = static_pointer_cast<ShapeRenderComponent>(entity->getComponent(ComponentType::SHAPE_RENDER));
    shapeComp->getShape()->setFillColor(sf::Color::Green);
    auto velComp = static_pointer_cast<VelocityComponent>(entity->getComponent(ComponentType::VELOCITY));
    velComp->velocity.set(0.01f, 0.01f);
    GameSystem system{ entityManager, 500, 500 };
   
    system.mainLoop();

    return 0;
}