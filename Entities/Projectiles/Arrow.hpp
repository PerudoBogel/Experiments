#pragma once
#include "IProjectile.hpp"
#include "TrajectoryTypes.hpp"

class Arrow: public IProjectile
{
public:
    Arrow()
    {
        m_speed = 5;
        m_type = PROJECTILE_TYPE_ARROW;
        m_IControl.m_customData = TRAJECTORY_LINE;
        m_size.h = 8;
        m_size.w = 20;
    }
};