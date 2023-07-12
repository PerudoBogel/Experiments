#pragma once
#include "ProjectileBase.hpp"
#include "TrajectoryTypes.hpp"

class Orb: public ProjectileBase
{
public:
    Orb()
    {
        m_speed = 5;
        m_type = PROJECTILE_TYPE_ORB;
        m_customData = TRAJECTORY_LINE;
        m_size.h = 10;
        m_size.w = 20;
    }
};