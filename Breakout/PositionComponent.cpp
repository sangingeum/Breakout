#include "PositionComponent.hpp"

PositionComponent::PositionComponent()
	: Component(ComponentType::POSITION) 
{}
PositionComponent::PositionComponent(float x, float y)
	: Component(ComponentType::POSITION)
	, position(x, y)
{
}
PositionComponent::PositionComponent(const Vec2& v)
	: Component(ComponentType::POSITION)
	, position(v)
{
}