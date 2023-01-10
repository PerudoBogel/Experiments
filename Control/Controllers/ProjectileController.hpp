#pragma once

#include "Controller.hpp"
#include "ITrajectory.hpp"

using namespace std;

class ProjectileController: public Controller
{
public:
	ProjectileController() = delete;
	ProjectileController(weak_ptr<World> pWorld, weak_ptr<IEntity> pEntity);
    
	void Run();
	ControllerType GetType(){return CONTROL_PROJECTILE;}

private:
	unique_ptr<ITrajectory> m_pTrajectory;
};