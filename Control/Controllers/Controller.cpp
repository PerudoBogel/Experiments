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
		weak_ptr<IEntity> pEntity) :
		m_pEntity(pEntity), m_pWorld(pWorld),
		m_isAlive(true)
{
}

int Controller::Move(Coordinates step)
{
	int rVal = CANNOT_MOVE;

	auto lockedWorld = m_pWorld.lock();
	auto lockedEntity = m_pEntity.lock();
	if(!lockedWorld || !lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		auto lockedMoveEntity = lockedEntity->getIMove().lock();

		float vectorLength = sqrt(pow(step.x, 2) + pow(step.y, 2));
		float scaler = *lockedMoveEntity->m_pSpeed / vectorLength;
		step *= scaler;

		if (step != Coordinates(0, 0))
		{
			if (ActionMoveAndPush::Execute(lockedWorld, lockedMoveEntity, step)
					== ActionMoveAndPush::DONE)
			{
				rVal = DONE;
			}
			else if (ActionMoveAndPush::Execute(lockedWorld, lockedMoveEntity,
					Coordinates(step.x, 0)) == ActionMoveAndPush::DONE)
			{
				rVal = DONE;
			}
			else if (ActionMoveAndPush::Execute(lockedWorld, lockedMoveEntity,
					Coordinates(0, step.y)) == ActionMoveAndPush::DONE)
			{
				rVal = DONE;
			}
		}
	}

	return rVal;
}

int Controller::Attack(shared_ptr<IEntity> pTarget)
{
	int rVal = CANNOT_ATTACK;

	auto lockedEntity = m_pEntity.lock();
	if(!lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		auto attacker = lockedEntity->getIAttack().lock();
		auto defender = pTarget->getIAttack().lock();

		auto status = ActionAttack::Execute(attacker, defender);
		if (ActionAttack::DONE == status)
		{
			rVal = DONE;
		}
	}
	return rVal;
}

void Controller::Die()
{
	auto lockedWorld = m_pWorld.lock();
	if(m_pEntity.lock() && lockedWorld)
	{
		lockedWorld->deleteEntity(m_pEntity);
	}
	m_isAlive = false;
}

int Controller::Shoot(float direction)
{
	auto lockedWorld = m_pWorld.lock();
	auto lockedEntity = m_pEntity.lock();
	if(!lockedWorld || !lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		auto lockedWorldEntity = lockedEntity->getIWorld().lock();

		auto arrow = make_shared<Arrow>();
		arrow->m_position = *lockedWorldEntity->m_pPosition;
		arrow->m_position.phi = direction;

		lockedWorld->setEntity(static_cast<shared_ptr<IEntity>>(arrow));
	}

	return 1;
}

void Controller::Run()
{
	auto lockedEntity = m_pEntity.lock();
	if(!lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		if(!lockedEntity->getIAttack().lock()->m_isAlive)
		{
			Die();
		}
	}
}