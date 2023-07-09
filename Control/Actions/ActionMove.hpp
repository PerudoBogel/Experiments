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

	static bool isEndOfWorld(std::shared_ptr<World> pWorld, IMoveEntity &entity)
	{
		auto lockedMap = pWorld->getMap().lock();

		bool rVal = false;
		auto colissionBox = Box(entity.m_size,entity.m_position);

		auto mapField = lockedMap->getBox(colissionBox);
		for (auto mapSector : *mapField.get())
			if (!mapSector)
				rVal = true;

		return rVal;
	}

	static shared_ptr<IEntity> isPlaceTaken(std::shared_ptr<World> pWorld, IMoveEntity& entity)
	{
		shared_ptr<IEntity> rVal = nullptr;

		auto lockedEntities = pWorld->getEntities();

		for (auto testModel : lockedEntities)
		{
			IMoveEntity moveEntity;
			if(!IEntity::getInterface(testModel.second, moveEntity))
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

		auto tmpMoveEntity = entity;
		tmpMoveEntity.m_position += step;
		tmpMoveEntity.m_hitbox.update(tmpMoveEntity.m_position);

		if(isEndOfWorld(pWorld, tmpMoveEntity))
			rVal = END_OF_MAP;
		else if (pCollisionEntity = isPlaceTaken(pWorld, tmpMoveEntity))
			rVal = CANNOT_MOVE;

		if(rVal == DONE)
		{	
			entity.m_position = tmpMoveEntity.m_position;
			entity.m_hitbox = tmpMoveEntity.m_hitbox;
		}

		return rVal;
	}
private:
	ActionMove() = delete;
};

#endif /* ACTIONS_ACTIONMOVE_HPP_ */