#include "Entity.hpp"


Entity::Entity(size_t id)
	: m_id(id)
{}
void Entity::destroy() {
	toDestroy = true;
}
size_t Entity::getId() {
	return m_id;
}
std::shared_ptr<Component> Entity::addComponent(ComponentType type) {
	
	if (m_componentMap.find(type) != m_componentMap.end()) {
		return m_componentMap[type];
	}
	else {
		std::shared_ptr<Component> comp;
		switch(type) {
		case ComponentType::POSITION:
			comp = std::make_shared<PositionComponent>();
			break;
		case ComponentType::VELOCITY:
			comp = std::make_shared<VelocityComponent>();
			break;
		case ComponentType::COLLISION:
			comp = std::make_shared<CollisionComponent>();
			break;
		case ComponentType::PLAYER_INPUT:
			comp = std::make_shared<PlayerInputComponent>();
			break;
		case ComponentType::SHAPE_RENDER:
			comp = std::make_shared<ShapeRenderComponent>();
			break;
		}
		m_componentMap[type] = comp;
		return comp;
	}
}
void Entity::removeComponent(ComponentType type) {
	m_componentMap.erase(type);
}
bool Entity::hasComponent(ComponentType type) {
	if (m_componentMap.find(type) != m_componentMap.end()) {
		return true;
	}
	return false;
}
std::vector<ComponentType> Entity::getComponentTypes() const {
	std::vector<ComponentType> types;
	for (const auto& pair : m_componentMap) {
		types.push_back(pair.first);
	}
	return types;
}

std::shared_ptr<Component> Entity::getComponent(ComponentType type) {
	if (m_componentMap.find(type) != m_componentMap.end()) {
		return m_componentMap[type];
	}
	return std::shared_ptr<Component>(nullptr);
}