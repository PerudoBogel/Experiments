/*
 * AI.hpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#ifndef AI_AI_HPP_
#define AI_AI_HPP_

#include "World.hpp"
#include "AIController.hpp"
#include "Controller.hpp"

#include <memory>
#include <algorithm>
#include <map>

using namespace std;

class AI
{
public:
	AI(weak_ptr<World> pWorld):
	m_pWorld(pWorld)
	{
		updateControllers();
	}

	void Run()
	{
		updateControllers();

		for(auto pController: m_controllers)
		{
			pController.second->Run();
		}
	}

	shared_ptr<AIController> getController(shared_ptr<IEntity> pEntity)
	{
		shared_ptr<AIController> rVal;
		
		updateControllers();
		
		try
		{
			rVal = m_controllers.at(pEntity.get());
		}
		catch(out_of_range except)
		{
		}

		return rVal;
	}
private:
	weak_ptr<World> m_pWorld;
	map<void*,shared_ptr<AIController>> m_controllers;
	
	void updateControllers()
	{
		for(auto pEntity: *m_pWorld.lock()->getEntities().lock().get())
		{
			auto worldEntity = pEntity->getIWorld().lock();
			shared_ptr<AIController> pController;

			if(IModel::CONTROL_AI == *worldEntity->m_pControl)
			{
				try
				{
					m_controllers.at(pEntity.get());
				}
				catch(out_of_range except)
				{
					m_controllers[pEntity.get()] = make_shared<AIController>(make_unique<Controller>(m_pWorld, pEntity));
				}
			}
		}
	}
};

#endif /* AI_AI_HPP_ */
