#include "Entity.hpp"

Entity::Entity(size_t id)
	: m_id(id)
{}
void Entity::destroy() {
	m_toDestroy = true;
}
bool Entity::isDestroyed() {
	return m_toDestroy;
}
size_t Entity::getId() {
	return m_id;
}

std::vector<ComponentType> Entity::getComponentTypes() {
	std::vector<ComponentType> types;
	if (hasComponent<ShapeRenderComponent>()) {
		types.push_back(ComponentType::SHAPE_RENDER);
	}
	if (hasComponent<CollisionComponent>()) {
		types.push_back(ComponentType::COLLISION);
	}
	if (hasComponent<PlayerInputComponent>()) {
		types.push_back(ComponentType::PLAYER_INPUT);
	}
	if (hasComponent<TransformationComponent>()) {
		types.push_back(ComponentType::TRANSFORMATION);
	}
	return types;
}
