/*
 * Controller.h
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_CONTROLLER_HPP_
#define UI_CONTROLLER_CONTROLLER_HPP_

#include "IModel.hpp"
#include "World.hpp"
#include "Coordinates.hpp"
#include <memory>

class Controller{
public:
	enum{
		DONE,
		CANNOT_MOVE,
		CANNOT_ATTACK
	};
	Controller(std::shared_ptr<World> pWorld, std::shared_ptr<IModel> pModel);
	int move(Coordinates step);
	int attack(Coordinates target);
	std::shared_ptr<IModel> m_model;
private:
	std::shared_ptr<World> m_pWorld;
};

#endif /* UI_CONTROLLER_CONTROLLER_HPP_ */
