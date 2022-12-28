/*
 * Controller.c
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */
#include "Controller.hpp"
#include <math.h>
#include "ActionAttack.hpp"
#include "ActionMoveAndPush.hpp"
#include "ActionMove.hpp"
#include "Debug.hpp"

Controller::Controller(std::shared_ptr<World> pWorld,
		std::shared_ptr<IModel> pModel) :
		m_model(pModel), m_pWorld(pWorld)
{
}

int Controller::move(Coordinates step)
{
	int retVal = DONE;

	float vectorLength = sqrt(pow(step.x, 2) + pow(step.y, 2));
	float scaler = m_model->m_speed / vectorLength;

	step *= scaler;

	if (step != Coordinates(0, 0))
	{
		if (ActionMoveAndPush::Execute(m_pWorld, m_model, step)
				== ActionMoveAndPush::DONE)
		{
		}
		else if (ActionMoveAndPush::Execute(m_pWorld, m_model,
				Coordinates(step.x, 0)) == ActionMoveAndPush::DONE)
		{
		}
		else if (ActionMoveAndPush::Execute(m_pWorld, m_model,
				Coordinates(0, step.y)) == ActionMoveAndPush::DONE)
		{
		}
		else
			retVal = CANNOT_MOVE;
	}

	return retVal;
}

int Controller::attack(IModel *target)
{
	int retVal = DONE;

	AttackModel attacker(*m_model.get()), defender(*target);

	if (ActionAttack::Execute(attacker, defender) != ActionAttack::DONE)
	{
		retVal = CANNOT_ATTACK;
	}
	return retVal;
}

int Controller::die()
{
	delete this;
	return 1;
}

int Controller::shoot(Coordinates direction)
{
	return 1;
}
