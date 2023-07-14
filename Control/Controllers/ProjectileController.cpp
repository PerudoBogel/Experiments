#include "ProjectileController.hpp"
#include "TrajectoryTypes.hpp"
#include "TrajectoryLine.hpp"

#include <assert.h>

ProjectileController::ProjectileController(weak_ptr<World> pWorld, shared_ptr<Entity>pEntity):
    ControllerBase(pWorld, pEntity)
{
    IControlEntity ControlEntity;
    IMoveEntity MoveEntity;

    if(Entity::getInterface(pEntity ,ControlEntity) && Entity::getInterface(pEntity ,MoveEntity))
    {
        switch(ControlEntity.m_customData)
        {
            case TRAJECTORY_LINE:
            default:
                m_pTrajectory = make_unique<TrajectoryLine>(MoveEntity.m_position, MoveEntity.m_speed, 1000);
                break;
        }
    }
}

void ProjectileController::Run()
{
    auto lockedEntity = m_pEntity;
    if(lockedEntity)
    {
        auto moveStep = m_pTrajectory->makeStep();
        shared_ptr<Entity> pCollissionEntity;

        if(!m_pTrajectory->ifInRange() && m_isAlive)
        {
            Die();
        }

        if(Move(moveStep, pCollissionEntity, false) != DONE)
        {
            if(pCollissionEntity)
            {
                Attack(pCollissionEntity);
                Die();
            }
        }
    }
    else{
        Die();
    }
}