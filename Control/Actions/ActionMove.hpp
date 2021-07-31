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
#include "IModel.hpp"
#include <vector>
#include <memory>

class ActionMove
{
public:
	enum
	{
		DONE, CANNOT_MOVE, END_OF_MAP
	};

	static int Execute(std::shared_ptr<World> pWorld, std::shared_ptr<IModel> pModel, Coordinates coordinates)
	{
		std::shared_ptr<Map> map = pWorld->getMap();
		int retVal = DONE;

		Box modelBox(pModel->getSize(), pModel->getPosition() + coordinates);

		if (modelBox.Xmax >= map->m_size.w * ISector::m_Size.w
				|| modelBox.Ymax >= map->m_size.h * ISector::m_Size.h)

			retVal = END_OF_MAP;

		else if (modelBox.Xmin < 0 || modelBox.Ymin < 0)

			retVal = END_OF_MAP;

		auto mapField = map->getBox(modelBox);
		for (auto mapSector : mapField)
			if (!mapSector)
				retVal = END_OF_MAP;

		for (auto testModel : *pWorld->getModels().get())
		{
			if (testModel.get() == pModel.get())
				continue;

			Box testModelBox(testModel->getSize(), testModel->getPosition());
			if (modelBox.isCollision(testModelBox))
			{
				retVal = CANNOT_MOVE;
				break;
			}
		}

		if(retVal == DONE)
			pModel->move(coordinates);

		return retVal;
	}
private:
	ActionMove() = delete;
};

#endif /* ACTIONS_ACTIONMOVE_HPP_ */
