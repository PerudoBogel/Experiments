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
#include "AllocationPool.hpp"

#include <assert.h>
#include <math.h>

ControllerBase::ControllerBase(weak_ptr<World> pWorld,
		shared_ptr<Entity> pEntity) :
		m_pEntity(pEntity), m_pWorld(pWorld),
		m_isAlive(true)
{
}

int ControllerBase::Move(Coordinates step, bool allowSlide)
{
	shared_ptr<Entity> dummy;

	return Move(step, dummy, allowSlide);
}

int ControllerBase::Move(Coordinates step, shared_ptr<Entity> &pCollisionEntity, bool allowSlide)
{
	int rVal = CANNOT_MOVE;

	auto lockedWorld = m_pWorld.lock();
	IMoveEntity moveEntity;

	if(!lockedWorld || !Entity::getInterface(m_pEntity, moveEntity))
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
				Entity::setInterface(m_pEntity, moveEntity);
			}
		}
	}

	return rVal;
}

int ControllerBase::Attack(shared_ptr<Entity> pTarget)
{
	int rVal = CANNOT_ATTACK;
	IAttackEntity attacker,defender;

	if(!Entity::getInterface(m_pEntity, attacker) || !Entity::getInterface(pTarget, defender))
	{
		Die();
	}

	if(m_isAlive)
	{
		auto status = ActionAttack::Execute(attacker, defender);
		if (ActionAttack::DONE == status)
		{
			rVal = DONE;
			Entity::setInterface(m_pEntity, attacker);
			Entity::setInterface(pTarget, defender);
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
	IMoveEntity moveEntity;
	if(!lockedWorld || !Entity::getInterface(m_pEntity, moveEntity))
	{
		Die();
	}

	if(m_isAlive)
	{
		auto startOffset = max(moveEntity.m_size.h,moveEntity.m_size.w);

		auto rotationRad = atan(direction.y/ direction.x) ;
		if(direction.x < 0)
			rotationRad += PI;

		// check if eq is available and select projectile based on that
		IMoveEntity orbMoveEntity;
		auto orb = AllocationPool::makeAllocation<Orb>();
		Entity::getInterface(orb, orbMoveEntity);
		orbMoveEntity.m_position = moveEntity.m_position;
		orbMoveEntity.m_position.phi = rotationRad / (2 * PI) * 360;
		orbMoveEntity.m_position += Coordinates(startOffset * cos(rotationRad), startOffset * sin(rotationRad));
		Entity::setInterface(orb, orbMoveEntity);

		DEBUG_DUMP_VAR(orbMoveEntity.m_position.x);
		DEBUG_DUMP_VAR(orbMoveEntity.m_position.y);
		DEBUG_DUMP_VAR(orbMoveEntity.m_position.phi);

		lockedWorld->setEntity(static_cast<shared_ptr<Entity>>(orb));
	}

	return 1;
}

void ControllerBase::Run()
{
	IAttackEntity attackEntity;
	if(!Entity::getInterface(m_pEntity, attackEntity))
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