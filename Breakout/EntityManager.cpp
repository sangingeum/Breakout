#include "EntityManager.hpp"


EntityManager::EntityManager() {};
void EntityManager::update() {
	// Add
	for (auto entity : m_toAdd) {
		m_entities.push_back(entity);
		for (auto type : entity->getComponentTypes()) {
			m_entityMap[type].push_back(entity);
		}
	}
	//Remove
	// TODO
}

size_t EntityManager::getNextID() {
	return m_entityID++;
}

std::shared_ptr<Entity> EntityManager::addEntity(std::vector<ComponentType> componentTypes) {
	auto entity = std::shared_ptr<Entity>(new Entity(getNextID()));
	for (auto type : componentTypes) {
		entity->addComponent(type);
	}
	m_toAdd.push_back(entity);
	return entity;
}

std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities() {
	return m_entities;
}
std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities(ComponentType type) {
	return m_entityMap[type];
}