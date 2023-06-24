#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "PositionComponent.hpp"
#include "Entity.hpp"
class EntityManager {
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::unordered_map<ComponentType, std::vector<std::shared_ptr<Entity>>> m_entityMap;
	std::vector<std::shared_ptr<Entity>> m_toAdd;
	size_t m_entityID = 0;
public:
	EntityManager();
	void update();
	size_t getNextID();
	std::shared_ptr<Entity> addEntity(std::vector<ComponentType> types);
	std::vector<std::shared_ptr<Entity>>& getEntities();
	std::vector<std::shared_ptr<Entity>>& getEntities(ComponentType type);

};