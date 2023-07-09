#pragma once

#include "ControllerBase.hpp"
#include "ITrajectory.hpp"

using namespace std;

class ProjectileController: public ControllerBase
{
public:
	ProjectileController() = delete;
	ProjectileController(weak_ptr<World> pWorld, shared_ptr<IEntity> pEntity);
    
	void Run();
	ControllerType GetType(){return CONTROL_PROJECTILE;}

private:
	unique_ptr<ITrajectory> m_pTrajectory;
};