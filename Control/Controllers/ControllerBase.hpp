/*
 * Controller.h
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_CONTROLLER_HPP_
#define UI_CONTROLLER_CONTROLLER_HPP_

#include "Entity.hpp"
#include "World.hpp"
#include "Coordinates.hpp"

#include <memory>

using namespace std;

class ControllerBase{
public:
	enum{
		DONE,
		CANNOT_MOVE,
		CANNOT_ATTACK
	};

	ControllerBase() = delete;
	ControllerBase(weak_ptr<World> pWorld, shared_ptr<Entity> pEntity);
	virtual ~ControllerBase(){}
	
	virtual void Run();
	virtual ControllerType GetType(){return CONTROL_NONE;}

	int Move(Coordinates step, shared_ptr<Entity> &pCollisionEntity, bool allowSlide = true);
	int Move(Coordinates step, bool allowSlide = true);
	int Attack(shared_ptr<Entity> pTarget);
	void Die();
	int Shoot(Coordinates &direction);
	bool IfAlive(){return m_isAlive;};

	shared_ptr<Entity> m_pEntity;
protected:
	weak_ptr<World> m_pWorld;
	bool m_isAlive;
};

#endif /* UI_CONTROLLER_CONTROLLER_HPP_ */
