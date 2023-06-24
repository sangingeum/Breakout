#pragma once
#include "Component.hpp"
#include <SFML/Graphics.hpp>

enum class ShapeType {
	RECTANGLE,
	CIRCLE
};

class ShapeRenderComponent : public Component
{	
	std::shared_ptr<sf::Shape> m_shape;
	ShapeType m_type;
public:
	ShapeRenderComponent();
	ShapeRenderComponent(float radius);
	ShapeRenderComponent(float width, float height);
	std::shared_ptr<sf::Shape> getShape();
	ShapeType getShapeType();
};

