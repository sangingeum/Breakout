#include "ShapeRenderComponent.hpp"

ShapeRenderComponent::ShapeRenderComponent()
	: m_type(ShapeType::RECTANGLE)
	, m_shape(std::make_shared<sf::RectangleShape>(sf::RectangleShape({ 100.0f, 100.0f })))
{
	m_shape->setFillColor(sf::Color::Green);
}

ShapeType ShapeRenderComponent::getShapeType() {
	return m_type;
}

void ShapeRenderComponent::setShape(ShapeType type) {
	m_type = type;
	if (type == ShapeType::RECTANGLE) {
		m_shape = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape({ 100.0f, 100.0f }));
	}
	else {
		m_shape = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(30.0f));
	}
}