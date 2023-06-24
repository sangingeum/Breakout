#include "VelocityComponent.hpp"

VelocityComponent::VelocityComponent()
	: Component(ComponentType::VELOCITY) 
{}
VelocityComponent::VelocityComponent(float x, float y) 
	: Component(ComponentType::VELOCITY)
	, velocity(x, y)
{

}
VelocityComponent::VelocityComponent(const Vec2& v) 
	: Component(ComponentType::VELOCITY)
	, velocity(v)
{

}