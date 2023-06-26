#pragma once
#include "Component.hpp"
#include <SFML/Graphics.hpp>

enum class ShapeType {
	RECTANGLE,
	CIRCLE
};

class ShapeRenderComponent
{	
	std::shared_ptr<sf::Shape> m_shape;
	ShapeType m_type;
public:
	ShapeRenderComponent();
	template<class T> std::shared_ptr<T> getShape();
	ShapeType getShapeType();
	void toCircle(float radius);
	void toRectangle(float width, float height);
	void setColor(sf::Color color);
};
template<class T> std::shared_ptr<T> ShapeRenderComponent::getShape() {
	return std::static_pointer_cast<T>(m_shape);
}
