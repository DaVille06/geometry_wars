#include "EntityManager.h"
#include <algorithm>

EntityManager::EntityManager() { }

void EntityManager::update()
{
	// add entities from m_entitiesToAdd to the proper location(s)
	// add them to the vector of all entities
	// add them to the vector inside the map, with the tag as the key
	for (auto e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	// after we have added entities to add
	// clear the entity vec
	m_entitiesToAdd.clear();

	// remove dead entities from the vector of all entities
	removeDeadEntities(m_entities);

	// remove dead entities from each vector in the entity map
	// c++17 way of iterating through [key, value] pairs in a map
	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	m_entitiesToAdd.push_back(entity);
	return entity;
}

EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}

auto entityIsDead = [&](std::shared_ptr<Entity> entity) -> bool 
{
	return !entity->isActive();
};

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	auto entitiesIterator = std::remove_if(vec.begin(), vec.end(), entityIsDead);
	vec.erase(entitiesIterator, vec.end());
}