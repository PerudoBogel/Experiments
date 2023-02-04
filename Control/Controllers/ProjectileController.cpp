#include "ProjectileController.hpp"
#include "TrajectoryTypes.hpp"
#include "TrajectoryLine.hpp"

#include <assert.h>

ProjectileController::ProjectileController(weak_ptr<World> pWorld, shared_ptr<IEntity>pEntity):
    Controller(pWorld, pEntity)
{
    auto ControlEntity = m_pEntity->getIControl();
    auto MoveEntity = m_pEntity->getIMove();

    assert(ControlEntity.ifValid());
    assert(MoveEntity.ifValid());
    assert(m_pEntity->getIAttack().ifValid());

    switch(ControlEntity.m_customData)
    {
        case TRAJECTORY_LINE:
        default:
            m_pTrajectory = make_unique<TrajectoryLine>(*MoveEntity.m_pPosition, *MoveEntity.m_pSpeed, 1000);
            break;
    }
}

void ProjectileController::Run()
{
    auto lockedEntity = m_pEntity;
    if(lockedEntity)
    {
        auto MoveEntity = lockedEntity->getIMove();
        auto moveStep = m_pTrajectory->makeStep();
        shared_ptr<IEntity> pCollissionEntity;

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