#include "World.hpp"

#include <algorithm>

shared_ptr<vector<shared_ptr<IEntity>>> World::getEntitiesInBox(Box box)
{
	auto rVector = make_shared<vector<shared_ptr<IEntity>>>();

	for (auto pEntity : m_entities)
	{
		auto pWorldEntity = pEntity.second->getIWorld();

		if(!pWorldEntity.ifValid())
		{
			continue;
		}

		Box entityBox(*pWorldEntity.m_pSize, *pWorldEntity.m_pPosition);

		if (box.isCollision(entityBox))
		{
			rVector->push_back(pEntity.second);
		}
	}
	return rVector;
}

void World::setEntity(shared_ptr<IEntity> pEntity)
{
	auto key = pEntity.get();
	if (m_entities.find(key) == m_entities.end())
		m_entities.insert(pair(key,pEntity));
}

bool World::deleteEntity(shared_ptr<IEntity> pEntity)
{
	bool rVal = false;
	auto key = pEntity.get();
	if (m_entities.find(key) != m_entities.end())
	{
		m_entities.erase(key);
		rVal = true;
	}
	return rVal;
}