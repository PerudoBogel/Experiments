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
#include "EntityFactory.hpp"

#include <assert.h>
#include <math.h>

Controller::Controller(weak_ptr<World> pWorld,
		shared_ptr<IEntity> pEntity) :
		m_pEntity(pEntity), m_pWorld(pWorld),
		m_isAlive(true)
{
}

int Controller::Move(Coordinates step, bool allowSlide)
{
	shared_ptr<IEntity> dummy;

	return Move(step, dummy, allowSlide);
}

int Controller::Move(Coordinates step, shared_ptr<IEntity> &pCollisionEntity, bool allowSlide)
{
	int rVal = CANNOT_MOVE;

	auto lockedWorld = m_pWorld.lock();
	auto lockedEntity = m_pEntity;
	if(!lockedWorld || !lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		IMoveEntity moveEntity;

		if (step != Coordinates(0, 0) && lockedEntity->getIMove(moveEntity))
		{
			if (ActionMove::Execute(lockedWorld, moveEntity, step, pCollisionEntity)
					== ActionMove::DONE)
			{
				rVal = DONE;
			}
			else if(allowSlide)
				if (ActionMove::Execute(lockedWorld, moveEntity,
						Coordinates(step.x, 0), pCollisionEntity) == ActionMove::DONE)
				{
					rVal = DONE;
				}
				else if (ActionMove::Execute(lockedWorld, moveEntity,
						Coordinates(0, step.y), pCollisionEntity) == ActionMove::DONE)
				{
					rVal = DONE;
				}
			if(rVal == DONE)
			{
				lockedEntity->setIMove(moveEntity);
			}
		}
	}

	return rVal;
}

int Controller::Attack(shared_ptr<IEntity> pTarget)
{
	int rVal = CANNOT_ATTACK;
	auto lockedEntity = m_pEntity;
	if(!lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		IAttackEntity attacker,defender;

		if(lockedEntity->getIAttack(attacker) && pTarget->getIAttack(defender))
		{
			auto status = ActionAttack::Execute(attacker, defender);
			if (ActionAttack::DONE == status)
			{
				rVal = DONE;
				lockedEntity->setIAttack(attacker);
				pTarget->setIAttack(defender);
			}
		}
	}
	return rVal;
}

void Controller::Die()
{
	auto lockedWorld = m_pWorld.lock();
   	auto lockedEntity = m_pEntity;
    if(lockedEntity && lockedWorld)
    {
            lockedWorld->deleteEntity(lockedEntity);
    }
	m_isAlive = false;
}

int Controller::Shoot(Coordinates &direction)
{
	auto lockedWorld = m_pWorld.lock();
	auto lockedEntity = m_pEntity;
	if(!lockedWorld || !lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		IWorldEntity worldEntity;
		if(lockedEntity->getIWorld(worldEntity))
		{
			auto startOffset = max(worldEntity.m_size.h,worldEntity.m_size.w);

			auto rotationRad = atan(direction.y/ direction.x) ;
			if(direction.x < 0)
				rotationRad += PI;

			// check if eq is available and select projectile based on that
			IMoveEntity arrowMoveEntity;
			auto arrow = EntityFactory::makeEntity<Arrow>();
			arrow->getIMove(arrowMoveEntity);
			arrowMoveEntity.m_position = worldEntity.m_position;
			arrowMoveEntity.m_position.phi = rotationRad / (2 * PI) * 360;
			arrowMoveEntity.m_position += Coordinates(startOffset * cos(rotationRad), startOffset * sin(rotationRad));
			arrow->setIMove(arrowMoveEntity);

			lockedWorld->setEntity(static_cast<shared_ptr<IEntity>>(arrow));
		}
	}

	return 1;
}

void Controller::Run()
{
	auto lockedEntity = m_pEntity;
	if(!lockedEntity)
	{
		Die();
	}

	if(m_isAlive)
	{
		IAttackEntity attackEntity;
		if(!lockedEntity->getIAttack(attackEntity))
		{ 
			/*cannot die*/
		}
		else if(attackEntity.m_health <= 0)
		{
			Die();
		}
	}
}