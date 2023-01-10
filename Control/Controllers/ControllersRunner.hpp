#pragma once

#include "World.hpp"
#include "AIController.hpp"
#include "PlayerModelController.hpp"
#include "ProjectileController.hpp"
#include "ControllerType.hpp"
#include "Controller.hpp"
#include "Scope.hpp"

#include <memory>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class ControllersRunner
{
public:
	ControllersRunner(weak_ptr<World> pWorld, weak_ptr<Scope> pScope):
	m_pWorld(pWorld),
	m_pScope(pScope)
	{
		updateControllers();
	}

	void Run()
	{
		updateControllers();

		vector<void*> deadKeys;

		for(auto pController: m_controllers)
		{
			if(pController.second->IfAlive())
				pController.second->Run();
			else
				deadKeys.push_back(pController.first);
		}
		
		for(auto deadKey: deadKeys)
			m_controllers.erase(deadKey);
	}

	shared_ptr<Controller> getController(shared_ptr<IEntity> pEntity)
	{
		shared_ptr<Controller> rVal;
		auto key = pEntity.get();
		
		updateControllers();
		
		if(m_controllers.find(key) != m_controllers.end())
		{
			rVal = m_controllers.at(key);
		}

		return rVal;
	}
private:
	weak_ptr<World> m_pWorld;
	weak_ptr<Scope> m_pScope;
	map<void*,shared_ptr<Controller>> m_controllers;
	
	void updateControllers()
	{
		for(auto pEntity: *m_pWorld.lock()->getEntities().lock().get())
		{
			auto controlEntity = pEntity.second->getIControl().lock();
			auto key = pEntity.second.get();

			if(m_controllers.find(key) != m_controllers.end())
				continue;

			switch(controlEntity->m_controller)
            {
            case CONTROL_AI:
			    m_controllers.insert(pair(key,make_shared<AIController>(m_pWorld, pEntity.second)));
                break;
            case CONTROL_PLAYER:
			    m_controllers.insert(pair(key,make_shared<PlayerModelController>(m_pWorld, pEntity.second, m_pScope)));
                break;
            case CONTROL_PROJECTILE:
			    m_controllers.insert(pair(key,make_shared<ProjectileController>(m_pWorld, pEntity.second)));
                break;
            default:
			    m_controllers.insert(pair(key,make_shared<Controller>(m_pWorld, pEntity.second)));
                break;
            }
		}
	}
};
