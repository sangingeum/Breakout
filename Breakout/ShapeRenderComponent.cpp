#include "ShapeRenderComponent.hpp"

ShapeRenderComponent::ShapeRenderComponent()
	: m_type(ShapeType::RECTANGLE)
	, m_shape(std::make_shared<sf::RectangleShape>(sf::RectangleShape({ 100.0f, 100.0f })))
{
}
ShapeRenderComponent::ShapeRenderComponent(float radius)
	: m_type(ShapeType::CIRCLE)
	, m_shape(std::make_shared<sf::CircleShape>(sf::CircleShape(radius)))
{ 
}
ShapeRenderComponent::ShapeRenderComponent(float width, float height)
	: m_type(ShapeType::RECTANGLE)
	, m_shape(std::make_shared<sf::RectangleShape>(sf::RectangleShape({ width, height })))
{
}

std::shared_ptr<sf::Shape> ShapeRenderComponent::getShape() {
	return m_shape;
}
ShapeType ShapeRenderComponent::getShapeType() {
	return m_type;
}