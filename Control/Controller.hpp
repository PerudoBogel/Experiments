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

	Controller(weak_ptr<World> pWorld, shared_ptr<IEntity> pEntity);
	
	int move(Coordinates step);
	int attack(shared_ptr<IEntity> pTarget);
	int die();
	int shoot(float direction);

	shared_ptr<IEntity> m_pEntity;
private:
	weak_ptr<World> m_pWorld;
};

#endif /* UI_CONTROLLER_CONTROLLER_HPP_ */
