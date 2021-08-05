/*
 * Move.hpp
 *
 *  Created on: 22 maj 2020
 *      Author: Jurek
 */

#ifndef ACTIONS_ACTIONMOVEANDPUSH_HPP_
#define ACTIONS_ACTIONMOVEANDPUSH_HPP_

#include "IModel.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"
#include "ReactionPush.hpp"
#include "ActionMove.hpp"
#include <memory>
#include <vector>

class ActionMoveAndPush
{
public:
	enum
	{
		DONE, COULDNOT_PUSH, COULDNOT_MOVE
	};

	static int Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IModel> pModel, Coordinates coordinates)
	{
		int retVal = DONE;
		Box previousModelBox(pModel->getSize(), *pModel->m_position);
		Box modelBox(pModel->getSize(), *pModel->m_position + coordinates);
		for (auto testModel : *pWorld->getModels().get())
		{
			if (testModel.get() == pModel.get())
				continue;

			Box actorSearchBox(testModel->getSize(), *testModel->m_position);
			if (modelBox.isCollision(actorSearchBox))
			{
				Coordinates push = Box::ColissionDir(previousModelBox,
						actorSearchBox);
				if (Coordinates(0, 0) != push)
				{
					if (ReactionPush::Execute(pWorld, pModel, testModel, push) != ReactionPush::DONE)
					{
						retVal = COULDNOT_PUSH;
						break;
					}
				}
			}
		}
		if (retVal == DONE)
		{
			retVal = ActionMove::Execute(pWorld, pModel, coordinates);
			if (retVal != ActionMove::DONE)
				retVal = COULDNOT_MOVE;
		}

		return retVal;
	}
private:
	ActionMoveAndPush() = delete;
};

#endif /* ACTIONS_ACTIONMOVEANDPUSH_HPP_ */
