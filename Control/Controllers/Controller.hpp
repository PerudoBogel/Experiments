/*
 * Controller.h
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_CONTROLLER_HPP_
#define UI_CONTROLLER_CONTROLLER_HPP_

#include "IEntity.hpp"
#include "World.hpp"
#include "Coordinates.hpp"

#include <memory>

using namespace std;

class Controller{
public:
	enum{
		DONE,
		CANNOT_MOVE,
		CANNOT_ATTACK
	};

	Controller() = delete;
	Controller(weak_ptr<World> pWorld, shared_ptr<IEntity> pEntity);
	virtual ~Controller(){}
	
	virtual void Run();
	virtual ControllerType GetType(){return CONTROL_NONE;}

	int Move(Coordinates step, shared_ptr<IEntity> &pCollisionEntity, bool allowSlide = true);
	int Move(Coordinates step, bool allowSlide = true);
	int Attack(shared_ptr<IEntity> pTarget);
	void Die();
	int Shoot(Coordinates &direction);
	bool IfAlive(){return m_isAlive;};

protected:
	shared_ptr<IEntity> m_pEntity;
	weak_ptr<World> m_pWorld;
	bool m_isAlive;
};

#endif /* UI_CONTROLLER_CONTROLLER_HPP_ */
