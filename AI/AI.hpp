/*
 * AI.hpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#ifndef AI_AI_HPP_
#define AI_AI_HPP_

#include <memory>
#include <vector>

#include "World.hpp"
#include "AIController.hpp"
#include "Controller.hpp"

class AI
{
public:
	AI(std::shared_ptr<World> pWorld)
	{
		for (auto model : *pWorld->getModels())
			if (model->m_control == IModel::CONTROL_AI)
				m_AIControllers.push_back(
						std::make_shared<AIController>(
								Controller(pWorld, model)));
	}

	void Run()
	{
		for (auto bot : m_AIControllers)
			bot->Run();
	}

	std::shared_ptr<AIController> getController(std::shared_ptr<IModel> pModel)
	{
		std::shared_ptr<AIController> retVal;
		for (auto search : m_AIControllers)
			if (search->m_controller.m_model.get() == pModel.get()){
				retVal = search;
				break;
			}
		return retVal;
	}
	std::vector<std::shared_ptr<AIController>> m_AIControllers;
};

#endif /* AI_AI_HPP_ */
