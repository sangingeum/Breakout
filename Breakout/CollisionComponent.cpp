#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent() 
	: Component(ComponentType::COLLISION)
	, type(CollisionBoxType::RECTANGLE)
{
}

CollisionComponent::CollisionComponent(CollisionBoxType type)
	: Component(ComponentType::COLLISION)
	, type(type)
{
}