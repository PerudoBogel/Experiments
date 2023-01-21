#pragma once

#include "Coordinates.hpp"
#include "Box.hpp"
#include "ReactionPush.hpp"
#include "ActionMove.hpp"

#include <memory>
#include <vector>

// using namespace std;

// class ActionPush
// {
// public:
// 	enum Status
// 	{
// 		DONE, NO_PUSH
// 	};
// 	ActionMove() = delete;

// 	// static Status Execute(vector<shared_ptr<IMoveEntity>>toPush, shared_ptr<IMoveEntity> pPusher, Coordinates coordinates)
// 	// {
// 	// 	Status rVal = DONE;
// 	// 	Box currentPlace(*pPusher->m_pSize, *pPusher->m_pPosition);
// 	// 	Box newPlace(*pPusher->m_pSize, *pPusher->m_pPosition + coordinates);

// 	// 	for (auto testModel : *pWorld->getEntitiesInBox(newPlace).get())
// 	// 	{
// 	// 		auto lockedTestEntity = testModel.lock();
// 	// 		if(!lockedTestEntity)
// 	// 			continue;

// 	// 		auto lockedTestMoveEntity = lockedTestEntity->getIMove().lock();
// 	// 		if(!lockedTestMoveEntity)
// 	// 			continue;

// 	// 		if (lockedTestMoveEntity.get() == pMoveEntity.get())
// 	// 			continue;

// 	// 		if (!lockedTestMoveEntity->m_isCollidable)
// 	// 			continue;

// 	// 		Box actorSearchBox(*lockedTestMoveEntity->m_pSize, *lockedTestMoveEntity->m_pPosition);
// 	// 		Coordinates push = Box::ColissionDir(currentPlace, actorSearchBox);
// 	// 		if (Coordinates(0, 0) != push)
// 	// 		{
// 	// 			if (ReactionPush::DONE != ReactionPush::Execute(pWorld, pMoveEntity, lockedTestMoveEntity, push))
// 	// 			{
// 	// 				rVal = COULDNOT_PUSH;
// 	// 				break;
// 	// 			}
// 	// 		}
// 	// 	}
// 	// 	if (rVal == Status::DONE)
// 	// 	{
// 	// 		if (ActionMove::DONE != ActionMove::Execute(pWorld, pMoveEntity, coordinates))
// 	// 			rVal = COULDNOT_MOVE;
// 	// 	}

// 	// 	return rVal;
// 	// }
// private:
// };
