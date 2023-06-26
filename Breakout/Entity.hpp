#pragma once
#include "CollisionComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "TransformationComponent.hpp"
#include "ShapeRenderComponent.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <tuple>
class Entity {
	size_t m_id{ 0 };
	bool m_toDestroy = false;
	std::tuple<std::shared_ptr<TransformationComponent>
		, std::shared_ptr<CollisionComponent>
		, std::shared_ptr<PlayerInputComponent>
		, std::shared_ptr<ShapeRenderComponent>> m_components;

public:
	Entity() = delete;
	Entity(size_t id);
	void destroy();
	size_t getId();
	template <class T> std::shared_ptr<T> addComponent();
	template <class T> std::shared_ptr<T> getComponent();
	template <class T> void removeComponent();
	template <class T> bool hasComponent();
	std::vector<ComponentType> getComponentTypes();
};

template <class T> std::shared_ptr<T> Entity::addComponent() {
	auto newComp = std::shared_ptr<T>(new T());
	std::get<std::shared_ptr<T>>(m_components) = newComp;
	return newComp;
}
template <class T> void Entity::removeComponent() {
	std::get<std::shared_ptr<T>>(m_components).reset();
}
template <class T> std::shared_ptr<T> Entity::getComponent() {
	return std::get<std::shared_ptr<T>>(m_components);
}
template <class T> bool Entity::hasComponent() {
	if (std::get<std::shared_ptr<T>>(m_components))
		return true;
	return false;
}

