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

class ActionMove
{
public:
	enum Status
	{
		DONE, CANNOT_MOVE, END_OF_MAP
	};

	static bool isEndOfWorld(std::shared_ptr<World> pWorld, IMoveEntity &entity, Coordinates step)
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

	static shared_ptr<IEntity> isPlaceTaken(std::shared_ptr<World> pWorld, IMoveEntity& entity, Coordinates step)
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

	static Status Execute(std::shared_ptr<World> pWorld, IMoveEntity &entity, Coordinates step, shared_ptr<IEntity> &pCollisionEntity)
	{
		Status rVal = DONE;
		
		float vectorLength = sqrt(pow(step.x, 2) + pow(step.y, 2));
		float scaler = entity.m_speed / vectorLength;
		step *= scaler;
		auto nextPosition = entity.m_position + step;

		if(isEndOfWorld(pWorld, entity, step))
			rVal = END_OF_MAP;
		else if (pCollisionEntity = isPlaceTaken(pWorld, entity, step))
			rVal = CANNOT_MOVE;

		if(rVal == DONE)
		{	
			entity.m_position += step;
			entity.m_hitbox.update(entity.m_position);
		}

		return rVal;
	}
private:
	ActionMove() = delete;
};

#endif /* ACTIONS_ACTIONMOVE_HPP_ */