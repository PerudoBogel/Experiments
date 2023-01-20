/*
 * ActionMove.hpp
 *
 *  Created on: 22 maj 2020
 *      Author: Jurek
 */

#ifndef ACTIONS_ACTIONMOVE_HPP_
#define ACTIONS_ACTIONMOVE_HPP_

#include "World.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"

#include <vector>
#include <memory>
#include <assert.h>

class ActionMove
{
public:
	enum Status
	{
		DONE, CANNOT_MOVE, END_OF_MAP
	};

	static bool isEndOfWorld(std::shared_ptr<World> pWorld, std::shared_ptr<IMoveEntity> pEntity, Coordinates coordinates)
	{
		auto lockedMap = pWorld->getMap().lock();
		assert(lockedMap);

		bool rVal = false;
		Box modelBox(*pEntity->m_pSize, *pEntity->m_pPosition + coordinates);

		if (modelBox.Xmax >= lockedMap->m_size.w * ISector::m_Size.w
				|| modelBox.Ymax >= lockedMap->m_size.h * ISector::m_Size.h)
			rVal = true;
		else if (modelBox.Xmin < 0 || modelBox.Ymin < 0)
			rVal = true;

		auto mapField = lockedMap->getBox(modelBox);
		for (auto mapSector : *mapField.get())
			if (!mapSector)
				rVal = true;

		return rVal;
	}

	static std::shared_ptr<IEntity> isPlaceTaken(std::shared_ptr<World> pWorld, IMoveEntity& pEntity, Coordinates coordinates)
	{
		std::shared_ptr<IEntity> rVal = nullptr;

		auto lockedEntities = pWorld->getEntities().lock();
		Box modelBox(*pEntity->m_pSize, *pEntity->m_pPosition + coordinates);

		if(lockedEntities)
		{
			for (auto testModel : *lockedEntities.get())
			{
				auto testMoveEntity = testModel.second->getIMove();
				if(!testMoveEntity)
					continue;

				if (testMoveEntity == pEntity)
					continue;

				if(!testMoveEntity->m_isCollidable)
					continue;
				
				Box testModelBox(*testMoveEntity->m_pSize, *testMoveEntity->m_pPosition);
				if (modelBox.isCollision(testModelBox))
				{
					rVal = testModel.second;
					break;
				}
			}
		}

		return rVal;
	}

	static Status Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IMoveEntity> pEntity, Coordinates coordinates, std::shared_ptr<IEntity> &pCollisionEntity)
	{
		Status rVal = DONE;
		
		float vectorLength = sqrt(pow(coordinates.x, 2) + pow(coordinates.y, 2));
		float scaler = *pEntity->m_pSpeed / vectorLength;
		coordinates *= scaler;

		if(isEndOfWorld(pWorld, pEntity, coordinates))
			rVal = END_OF_MAP;
		else if (pCollisionEntity = isPlaceTaken(pWorld, pEntity, coordinates))
			rVal = CANNOT_MOVE;

		if(rVal == DONE)
		{
			*pEntity->m_pPosition += coordinates;
		}

		return rVal;
	}
private:
	ActionMove() = delete;
};

#endif /* ACTIONS_ACTIONMOVE_HPP_ */