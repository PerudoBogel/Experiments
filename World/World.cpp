#include "World.hpp"
#include <iostream>
#include <algorithm>

shared_ptr<vector<weak_ptr<IEntity>>> World::getEntitiesInBox(Box box)
{
	auto rVector = shared_ptr<vector<weak_ptr<IEntity>>>();

	for (auto pEntity : *m_entities.get())
	{
		auto pWorldEntity = pEntity->getIWorld().lock();
		Box projectileBox(*pWorldEntity->m_pSize, *pWorldEntity->m_pPosition);

		if (box.isCollision(projectileBox))
		{
			rVector->push_back(pEntity);
		}
	}
	return rVector;
}

void World::setEntity(std::shared_ptr<IEntity> pEntity)
{
	if (std::find((*m_entities).begin(), (*m_entities).end(), pEntity) == (*m_entities).end())
		m_entities->push_back(pEntity);
}