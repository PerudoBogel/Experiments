/*
 * Controller.c
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */
#include "Controller.hpp"
#include "ActionAttack.hpp"
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

int Controller::Move(Coordinates step, bool allowSlide)
{
	shared_ptr<IEntity> dummy;

	return Move(step, dummy, allowSlide);
}

int Controller::Move(Coordinates step, shared_ptr<IEntity> pCollisionEntity, bool allowSlide)
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
		auto lockedMoveEntity = lockedEntity->getIMove();

		if (step != Coordinates(0, 0))
		{
			if (ActionMove::Execute(lockedWorld, lockedMoveEntity, step, pCollisionEntity)
					== ActionMove::DONE)
			{
				rVal = DONE;
			}
			else if(allowSlide)
				if (ActionMove::Execute(lockedWorld, lockedMoveEntity,
						Coordinates(step.x, 0), pCollisionEntity) == ActionMove::DONE)
				{
					rVal = DONE;
				}
				else if (ActionMove::Execute(lockedWorld, lockedMoveEntity,
						Coordinates(0, step.y), pCollisionEntity) == ActionMove::DONE)
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
		auto attacker = lockedEntity->getIAttack();
		auto defender = pTarget->getIAttack();

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
	auto lockedEntity = m_pEntity.lock();
	if(lockedEntity && lockedWorld)
	{
		lockedWorld->deleteEntity(lockedEntity);
	}
	m_isAlive = false;
}

int Controller::Shoot(Coordinates &direction)
{
	auto lockedWorld = m_pWorld.lock();
	auto lockedEntity = m_pEntity.lock();
	if(!lockedWorld || !lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		auto lockedWorldEntity = lockedEntity->getIWorld();
		auto startOffset = max(lockedWorldEntity.m_pSize->h,lockedWorldEntity.m_pSize->w);

		auto rotationRad = atan(direction.y/ direction.x) ;
        if(direction.x < 0)
            rotationRad += PI;

		// check if eq is available and select projectile based on that

		auto arrow = make_shared<Arrow>(); //use factory
		arrow->m_position = *lockedWorldEntity.m_pPosition;
		arrow->m_position.phi = rotationRad / (2 * PI) * 360;
		arrow->m_position += Coordinates(startOffset * cos(rotationRad), startOffset * sin(rotationRad)); 

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
		auto attackEntity = lockedEntity->getIAttack();
		if(!attackEntity.ifValid())
		{ 
			/*cannot die*/
		}
		else if(!attackEntity.m_isAlive)
		{
			Die();
		}
	}
}