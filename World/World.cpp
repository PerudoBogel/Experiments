#include "World.hpp"

#include <algorithm>

shared_ptr<vector<weak_ptr<IEntity>>> World::getEntitiesInBox(Box box)
{
	auto rVector = make_shared<vector<weak_ptr<IEntity>>>();

	for (auto pEntity : *m_entities.get())
	{
		auto pWorldEntity = pEntity.second->getIWorld().lock();
		Box projectileBox(*pWorldEntity->m_pSize, *pWorldEntity->m_pPosition);

		if (box.isCollision(projectileBox))
		{
			rVector->push_back(pEntity.second);
		}
	}
	return rVector;
}

void World::setEntity(std::shared_ptr<IEntity> pEntity)
{
	auto key = pEntity.get();
	if (m_entities->find(key) == m_entities->end())
		m_entities->insert(pair(key,pEntity));
}

bool World::deleteEntity(weak_ptr<IEntity> pEntity)
{
	bool rVal = false;
	auto key = pEntity.lock().get();
	if (m_entities->find(key) != m_entities->end())
	{
		m_entities->at(key).reset();
		m_entities->erase(key);
		rVal = true;
	}
	return rVal;
}