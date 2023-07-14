#include "World.hpp"

#include <algorithm>

shared_ptr<vector<shared_ptr<Entity>>> World::getEntitiesInBox(Box box)
{
	auto rVector = make_shared<vector<shared_ptr<Entity>>>();

	for (auto pEntity : m_entities)
	{
		IMoveEntity moveEntity;
		if(!Entity::getInterface(pEntity.second, moveEntity))
		{
			continue;
		}

		Box entityBox(moveEntity.m_size, moveEntity.m_position);

		if (box.isCollision(entityBox))
		{
			rVector->push_back(pEntity.second);
		}
	}
	return rVector;
}

void World::setEntity(shared_ptr<Entity> pEntity)
{
	auto key = pEntity.get();
	if (m_entities.find(key) == m_entities.end() && m_newEntities.find(key) == m_newEntities.end())
		m_newEntities.insert(pair(key,pEntity));
}

bool World::deleteEntity(shared_ptr<Entity> pEntity)
{
	bool rVal = false;
	auto key = pEntity.get();
	if (m_entities.find(key) != m_entities.end())
	{
		m_deadEntities.insert(pair(key,pEntity));
		rVal = true;
	}
	return rVal;
}

void World::sync()
{
	for(auto entity: m_deadEntities)
	{
		m_entities.erase(entity.first);
	}
	m_deadEntities.clear();

	for(auto entity: m_newEntities)
	{
		m_entities.insert(entity);
	}
	m_newEntities.clear();
}