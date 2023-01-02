/*
 * Controller.c
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */
#include "Controller.hpp"
#include "ActionAttack.hpp"
#include "ActionMoveAndPush.hpp"
#include "ActionMove.hpp"
#include "Debug.hpp"
#include "Arrow.hpp"

#include <assert.h>
#include <math.h>

Controller::Controller(weak_ptr<World> pWorld,
		shared_ptr<IEntity> pEntity) :
		m_pEntity(pEntity), m_pWorld(pWorld)
{
}

int Controller::move(Coordinates step)
{
	auto lockedWorld = m_pWorld.lock();
	assert(lockedWorld);

	int rVal = DONE;

	auto lockedWorldEntity = m_pEntity->getIWorld().lock();

	if(lockedWorldEntity)
	{
		float vectorLength = sqrt(pow(step.x, 2) + pow(step.y, 2));
		float scaler = *lockedWorldEntity->m_pSpeed / vectorLength;
		step *= scaler;

		if (step != Coordinates(0, 0))
		{
			if (ActionMoveAndPush::Execute(lockedWorld, lockedWorldEntity, step)
					== ActionMoveAndPush::DONE)
			{
			}
			else if (ActionMoveAndPush::Execute(lockedWorld, lockedWorldEntity,
					Coordinates(step.x, 0)) == ActionMoveAndPush::DONE)
			{
			}
			else if (ActionMoveAndPush::Execute(lockedWorld, lockedWorldEntity,
					Coordinates(0, step.y)) == ActionMoveAndPush::DONE)
			{
			}
			else
			{
				rVal = CANNOT_MOVE;
			}
		}
	}else{
		rVal = CANNOT_MOVE;
	}

	return rVal;
}

int Controller::attack(shared_ptr<IEntity> pTarget)
{
	int rVal = DONE;


	auto attacker = m_pEntity->getIAttack().lock();
	auto defender = pTarget->getIAttack().lock();

	if(attacker && defender)
	{
		if (ActionAttack::Execute(attacker, defender) != ActionAttack::DONE)
		{
			rVal = CANNOT_ATTACK;
		}
	}
	return rVal;
}

int Controller::die()
{
	delete this;
	return 1;
}

int Controller::shoot(float direction)
{
	auto lockedWorld = m_pWorld.lock();
	assert(lockedWorld);

	auto lockedWorldEntity = m_pEntity->getIWorld().lock();
	assert(lockedWorldEntity);

    auto arrow = make_shared<Arrow>();
    arrow->m_position = *lockedWorldEntity->m_pPosition;
	arrow->m_position.phi = direction;

	lockedWorld->setEntity(static_cast<shared_ptr<IEntity>>(arrow));

	return 1;
}
