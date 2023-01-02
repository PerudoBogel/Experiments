/*
 * Move.hpp
 *
 *  Created on: 22 maj 2020
 *      Author: Jurek
 */

#ifndef ACTIONS_ACTIONMOVEANDPUSH_HPP_
#define ACTIONS_ACTIONMOVEANDPUSH_HPP_

#include "IWorldEntity.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"
#include "ReactionPush.hpp"
#include "ActionMove.hpp"

#include <memory>
#include <vector>

class ActionMoveAndPush
{
public:
	enum Status
	{
		DONE, COULDNOT_PUSH, COULDNOT_MOVE
	};

	static Status Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IWorldEntity> pWorldEntity, Coordinates coordinates)
	{
		Status rVal = DONE;
		Box currentPlace(*pWorldEntity->m_pSize, *pWorldEntity->m_pPosition);
		Box newPlace(*pWorldEntity->m_pSize, *pWorldEntity->m_pPosition + coordinates);

		for (auto testModel : *pWorld->getEntitiesInBox(newPlace).get())
		{
			auto lockedTestEntity = testModel.lock();
			if(!lockedTestEntity)
				continue;

			auto lockedTestWorldEntity = lockedTestEntity->getIWorld().lock();
			if(!lockedTestWorldEntity)
				continue;

			if (lockedTestWorldEntity.get() == pWorldEntity.get())
				continue;

			Box actorSearchBox(*lockedTestWorldEntity->m_pSize, *lockedTestWorldEntity->m_pPosition);
			Coordinates push = Box::ColissionDir(currentPlace, actorSearchBox);
			if (Coordinates(0, 0) != push)
			{
				if (ReactionPush::DONE != ReactionPush::Execute(pWorld, pWorldEntity, lockedTestWorldEntity, push))
				{
					rVal = COULDNOT_PUSH;
					break;
				}
			}
		}
		if (rVal == Status::DONE)
		{
			if (ActionMove::DONE != ActionMove::Execute(pWorld, pWorldEntity, coordinates))
				rVal = COULDNOT_MOVE;
		}

		return rVal;
	}
private:
	ActionMoveAndPush() = delete;
};

#endif /* ACTIONS_ACTIONMOVEANDPUSH_HPP_ */
