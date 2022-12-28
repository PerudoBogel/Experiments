/*
 * ReactionPush.hpp
 *
 *  Created on: 22 maj 2020
 *      Author: Jurek
 */

#ifndef REACTIONS_REACTIONPUSH_HPP_
#define REACTIONS_REACTIONPUSH_HPP_

#include "IModel.hpp"
#include "Coordinates.hpp"
#include "ActionMove.hpp"
#include <memory>

class ReactionPush
{
public:
	enum
	{
		DONE, CANNOT_BE_MOVED, CANNOT_MOVE
	};

	static int Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IModel> pPushingModel, std::shared_ptr<IModel> pPushedModel, Coordinates coordinates)
	{
		int retVal = CANNOT_BE_MOVED;

		if (pPushingModel->m_moveStrength > pPushedModel->m_moveStrength){

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
