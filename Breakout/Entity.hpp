#pragma once
#include "Component.hpp"
#include "CollisionComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "ShapeRenderComponent.hpp"
#include <memory>
#include <unordered_map>

class Entity {
	size_t m_id{ 0 };
	std::unordered_map<ComponentType, std::shared_ptr<Component>> m_componentMap;
	bool toDestroy = false;
public:
	Entity(size_t id);
	void destroy();
	size_t getId();
	std::shared_ptr<Component> addComponent(ComponentType type);
	void removeComponent(ComponentType type);
	bool hasComponent(ComponentType type);
	std::vector<ComponentType> getComponentTypes() const;
	std::shared_ptr<Component> getComponent(ComponentType type);

};