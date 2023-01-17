#include "ProjectileController.hpp"
#include "TrajectoryTypes.hpp"
#include "TrajectoryLine.hpp"


ProjectileController::ProjectileController(weak_ptr<World> pWorld, weak_ptr<IEntity> pEntity) :
    Controller(pWorld, pEntity)
{
    auto ControlEntity = m_pEntity.lock()->getIControl().lock();
    auto MoveEntity = m_pEntity.lock()->getIMove().lock();

    switch(ControlEntity->m_customData)
    {
        case TRAJECTORY_LINE:
        default:
            m_pTrajectory = make_unique<TrajectoryLine>(*MoveEntity->m_pPosition, *MoveEntity->m_pSpeed, 1000);
            break;
    }
}

void ProjectileController::Run()
{
    auto lockedEntity = m_pEntity.lock();

    if(lockedEntity)
    {
        auto MoveEntity = lockedEntity->getIMove().lock();
        auto moveStep = m_pTrajectory->makeStep();
        shared_ptr<IEntity> collissionEntity;

        if(Move(moveStep, collissionEntity, false) != DONE)
        {
            if(collissionEntity)
            {
                Attack(collissionEntity);
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