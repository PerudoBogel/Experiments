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

	static Status Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IMoveEntity> pMoveEntity, Coordinates coordinates)
	{
		Status rVal = DONE;
		Box currentPlace(*pMoveEntity->m_pSize, *pMoveEntity->m_pPosition);
		Box newPlace(*pMoveEntity->m_pSize, *pMoveEntity->m_pPosition + coordinates);

		for (auto testModel : *pWorld->getEntitiesInBox(newPlace).get())
		{
			auto lockedTestEntity = testModel.lock();
			if(!lockedTestEntity)
				continue;

			auto lockedTestMoveEntity = lockedTestEntity->getIMove().lock();
			if(!lockedTestMoveEntity)
				continue;

			if (lockedTestMoveEntity.get() == pMoveEntity.get())
				continue;

			if (!lockedTestMoveEntity->m_isCollidable)
				continue;

			Box actorSearchBox(*lockedTestMoveEntity->m_pSize, *lockedTestMoveEntity->m_pPosition);
			Coordinates push = Box::ColissionDir(currentPlace, actorSearchBox);
			if (Coordinates(0, 0) != push)
			{
				if (ReactionPush::DONE != ReactionPush::Execute(pWorld, pMoveEntity, lockedTestMoveEntity, push))
				{
					rVal = COULDNOT_PUSH;
					break;
				}
			}
		}
		if (rVal == Status::DONE)
		{
			if (ActionMove::DONE != ActionMove::Execute(pWorld, pMoveEntity, coordinates))
				rVal = COULDNOT_MOVE;
		}

		return rVal;
	}
private:
	ActionMoveAndPush() = delete;
};

#endif /* ACTIONS_ACTIONMOVEANDPUSH_HPP_ */
