#include <vector>
#include <memory>
#include <unordered_map>
#include "Entity.hpp"
class EntityManager {
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::unordered_map<ComponentType, std::vector<std::shared_ptr<Entity>>> m_entityMap;
	std::vector<std::shared_ptr<Entity>> m_toAdd;
	size_t m_entityID = 0;
public:
	void update();
	void createEntity();



};