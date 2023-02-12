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

	static bool isEndOfWorld(std::shared_ptr<World> pWorld, IMoveEntity &entity, Coordinates coordinates)
	{
		// auto lockedMap = pWorld->getMap().lock();
		// assert(lockedMap);

		// bool rVal = false;


		// auto mapField = lockedMap->getBox(modelBox);
		// for (auto mapSector : *mapField.get())
		// 	if (!mapSector)
		// 		rVal = true;

		// return rVal;
		return false;
	}

	static shared_ptr<IEntity> isPlaceTaken(std::shared_ptr<World> pWorld, IMoveEntity& entity, Coordinates coordinates)
	{
		shared_ptr<IEntity> rVal = nullptr;

		auto lockedEntities = pWorld->getEntities();

		for (auto testModel : lockedEntities)
		{
			IMoveEntity moveEntity;
			if(!testModel.second->getIMove(moveEntity))
				continue;

			if (moveEntity == entity)
				continue;

			if(!moveEntity.m_isCollidable)
				continue;
			
			if (entity.m_hitbox.isCollision(moveEntity.m_hitbox))
			{
				rVal = testModel.second;
				break;
			}
		}
		
		return rVal;
	}

	static Status Execute(std::shared_ptr<World> pWorld, IMoveEntity &entity, Coordinates coordinates, shared_ptr<IEntity> &pCollisionEntity)
	{
		Status rVal = DONE;
		
		float vectorLength = sqrt(pow(coordinates.x, 2) + pow(coordinates.y, 2));
		float scaler = entity.m_speed / vectorLength;
		coordinates *= scaler;

		if(isEndOfWorld(pWorld, entity, coordinates))
			rVal = END_OF_MAP;
		else if (pCollisionEntity = isPlaceTaken(pWorld, entity, coordinates))
			rVal = CANNOT_MOVE;

		if(rVal == DONE)
		{	
			entity.m_position += coordinates;
		}

		return rVal;
	}
private:
	ActionMove() = delete;
};

#endif /* ACTIONS_ACTIONMOVE_HPP_ */