/*
 * ReactionPush.hpp
 *
 *  Created on: 22 maj 2020
 *      Author: Jurek
 */

#ifndef REACTIONS_REACTIONPUSH_HPP_
#define REACTIONS_REACTIONPUSH_HPP_

#include "IWorldEntity.hpp"
#include "Coordinates.hpp"
#include "ActionMove.hpp"
#include <memory>

class ReactionPush
{
public:
	enum Status
	{
		DONE, CANNOT_BE_MOVED, CANNOT_MOVE
	};

	static Status Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IWorldEntity> pPushingModel, std::shared_ptr<IWorldEntity> pPushedModel, Coordinates coordinates)
	{
		Status retVal = CANNOT_BE_MOVED;

		if (*pPushingModel->m_pMoveStrength > *pPushedModel->m_pMoveStrength){

			if (ActionMove::Execute(pWorld, pPushedModel, coordinates) == ActionMove::DONE)
				retVal = DONE;
			else
				retVal = CANNOT_MOVE;
		}

		return retVal;
	}
private:
	ReactionPush() = delete;
};

#endif /* REACTIONS_REACTIONPUSH_HPP_ */
