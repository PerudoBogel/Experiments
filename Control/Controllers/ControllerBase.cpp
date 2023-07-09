/*
 * Controller.c
 *
 *  Created on: 15 maj 2020
 *      Author: Jurek
 */
#include "ControllerBase.hpp"
#include "ActionAttack.hpp"
#include "ActionMove.hpp"
#include "Debug.hpp"
#include "Orb.hpp"
#include "EntityFactory.hpp"

#include <assert.h>
#include <math.h>

ControllerBase::ControllerBase(weak_ptr<World> pWorld,
		shared_ptr<IEntity> pEntity) :
		m_pEntity(pEntity), m_pWorld(pWorld),
		m_isAlive(true)
{
}

int ControllerBase::Move(Coordinates step, bool allowSlide)
{
	shared_ptr<IEntity> dummy;

	return Move(step, dummy, allowSlide);
}

int ControllerBase::Move(Coordinates step, shared_ptr<IEntity> &pCollisionEntity, bool allowSlide)
{
	int rVal = CANNOT_MOVE;

	auto lockedWorld = m_pWorld.lock();
	IMoveEntity moveEntity;

	if(!lockedWorld || !IEntity::getInterface(m_pEntity, moveEntity))
	{
		Die();
	}

	if(m_isAlive)
	{
		if (step != Coordinates(0, 0))
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
				IEntity::setInterface(m_pEntity, moveEntity);
			}
		}
	}

	return rVal;
}

int ControllerBase::Attack(shared_ptr<IEntity> pTarget)
{
	int rVal = CANNOT_ATTACK;
	IAttackEntity attacker,defender;

	if(!IEntity::getInterface(m_pEntity, attacker) || !IEntity::getInterface(m_pEntity, defender))
	{
		Die();
	}

	if(m_isAlive)
	{
		auto status = ActionAttack::Execute(attacker, defender);
		if (ActionAttack::DONE == status)
		{
			rVal = DONE;
			IEntity::setInterface(m_pEntity, attacker);
			IEntity::setInterface(pTarget, defender);
		}
	}
	return rVal;
}

void ControllerBase::Die()
{
	auto lockedWorld = m_pWorld.lock();
    if(m_pEntity && lockedWorld)
    {
        lockedWorld->deleteEntity(m_pEntity);
    }
	m_isAlive = false;
}

int ControllerBase::Shoot(Coordinates &direction)
{
	auto lockedWorld = m_pWorld.lock();
	IWorldEntity worldEntity;
	if(!lockedWorld || !IEntity::getInterface(m_pEntity, worldEntity))
	{
		Die();
	}

	if(m_isAlive)
	{
		auto startOffset = max(worldEntity.m_size.h,worldEntity.m_size.w);

		auto rotationRad = atan(direction.y/ direction.x) ;
		if(direction.x < 0)
			rotationRad += PI;

		// check if eq is available and select projectile based on that
		IMoveEntity orbMoveEntity;
		auto orb = EntityFactory::makeEntity<Orb>();
		IEntity::getInterface(orb, orbMoveEntity);
		orbMoveEntity.m_position = worldEntity.m_position;
		orbMoveEntity.m_position.phi = rotationRad / (2 * PI) * 360;
		orbMoveEntity.m_position += Coordinates(startOffset * cos(rotationRad), startOffset * sin(rotationRad));
		IEntity::setInterface(orb, orbMoveEntity);

		lockedWorld->setEntity(static_cast<shared_ptr<IEntity>>(orb));
	}

	return 1;
}

void ControllerBase::Run()
{
	IAttackEntity attackEntity;
	if(!IEntity::getInterface(m_pEntity, attackEntity))
	{
		Die();
	}

	if(m_isAlive)
	{
		if(attackEntity.m_health <= 0)
		{
			Die();
		}
	}
}