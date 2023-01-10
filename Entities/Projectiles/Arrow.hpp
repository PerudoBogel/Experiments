#pragma once
#include "IProjectile.hpp"
#include "TrajectoryTypes.hpp"

class Arrow: public IProjectile
{
public:
    Arrow()
    {
        m_speed = 5;
        m_pIControl->m_customData = TRAJECTORY_LINE;
    }
};