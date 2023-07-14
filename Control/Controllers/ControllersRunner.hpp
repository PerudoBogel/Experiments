#pragma once

#include "World.hpp"
#include "AIController.hpp"
#include "PlayerModelController.hpp"
#include "ProjectileController.hpp"
#include "ControllerBase.hpp"
#include "Scope.hpp"
#include "Window2d.hpp"

#include <memory>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class ControllersRunner
{
public:
	ControllersRunner(weak_ptr<World> pWorld, weak_ptr<Scope> pScope, Window2d* pWindow):
	m_pWorld(pWorld),
	m_pScope(pScope),
	m_pWindow(pWindow)
	{
		updateControllers();
	}

	void Run()
	{
		updateControllers();

		vector<Entity*> deadKeys;

		for(auto pController: m_controllers)
		{
			if(pController.second->IfAlive())
				pController.second->Run();
			else
				deadKeys.push_back(pController.first);
		}
		for(auto deadKey: deadKeys)
		{
			m_controllers.erase(deadKey);
		}
		m_pWorld.lock()->sync();
	}

	shared_ptr<ControllerBase> getController(Entity *pEntity)
	{
		shared_ptr<ControllerBase> rVal;
		auto key = pEntity;
		
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
	Window2d* m_pWindow;
	map<Entity*,shared_ptr<ControllerBase>> m_controllers;
	
	void updateControllers()
	{
		for(auto pEntity: m_pWorld.lock()->getEntities())
		{
			IControlEntity controlEntity;

			if(!Entity::getInterface(pEntity.second, controlEntity))
			{
				continue;
			}
			auto key = pEntity.second.get();

			if(m_controllers.find(key) != m_controllers.end())
				continue;

			switch(controlEntity.m_controller)
            {
            case CONTROL_AI:
			    m_controllers.insert(pair(key,make_shared<AIController>(m_pWorld, pEntity.second)));
                break;
            case CONTROL_PLAYER:
			    m_controllers.insert(pair(key,make_shared<PlayerModelController>(m_pWorld, pEntity.second, m_pScope, m_pWindow)));
                break;
            case CONTROL_PROJECTILE:
			    m_controllers.insert(pair(key,make_shared<ProjectileController>(m_pWorld, pEntity.second)));
                break;
            default:
			    m_controllers.insert(pair(key,make_shared<ControllerBase>(m_pWorld, pEntity.second)));
                break;
            }
		}
	}
};
