#include "ShapeRenderComponent.hpp"

ShapeRenderComponent::ShapeRenderComponent()
	: m_type(ShapeType::RECTANGLE)
	, m_shape(std::make_shared<sf::RectangleShape>(sf::RectangleShape({ 100.0f, 100.0f })))
{
	m_shape->setFillColor(sf::Color::Green);
	m_shape->setOrigin({ 50.f, 50.f });
}

ShapeType ShapeRenderComponent::getShapeType() {
	return m_type;
}

void ShapeRenderComponent::toCircle(float radius) {
	m_type = ShapeType::CIRCLE;
	m_shape = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(radius));
	m_shape->setOrigin({ radius, radius });
}

void ShapeRenderComponent::toRectangle(float width, float height) {
	m_type = ShapeType::RECTANGLE;
	m_shape = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape({ width, height }));
	m_shape->setOrigin({ width/2.0f, height/2.0f });
}

void ShapeRenderComponent::setColor(sf::Color color) {
	m_shape->setFillColor(color);
}

void ShapeRenderComponent::setOutlineColor(sf::Color color) {
	m_shape->setOutlineColor(color);
	m_shape->setOutlineThickness(2.0f);
}