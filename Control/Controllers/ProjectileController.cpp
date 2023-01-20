#include "ProjectileController.hpp"
#include "TrajectoryTypes.hpp"
#include "TrajectoryLine.hpp"

#include <assert.h>

ProjectileController::ProjectileController(weak_ptr<World> pWorld, weak_ptr<IEntity>pEntity):
    Controller(pWorld, pEntity)
{
    auto ControlEntity = m_pEntity.lock()->getIControl();
    auto MoveEntity = m_pEntity.lock()->getIMove();

    assert(ControlEntity.ifValid());
    assert(MoveEntity.ifValid());
    assert(m_pEntity.lock()->getIAttack().ifValid());

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
    auto lockedEntity = m_pEntity.lock();
    if(lockedEntity)
    {
        auto MoveEntity = lockedEntity->getIMove();
        auto moveStep = m_pTrajectory->makeStep();
        shared_ptr<IEntity> pCollissionEntity;

        if(Move(moveStep, pCollissionEntity, false) != DONE)
        {
            if(pCollissionEntity)
            {
                Attack(pCollissionEntity);
                Die();
            }
        }

        if(!m_pTrajectory->ifInRange() && m_isAlive)
        {
            Die();
        }
    }
    else{
        Die();
    }
}