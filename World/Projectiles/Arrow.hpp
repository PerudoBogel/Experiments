#pragma once
#include "IProjectile.hpp"

class Arrow: public IProjectile
{
public:
    Arrow()
    {
        m_speed = 3;
    }

    int getType(){return PROJECTILE_TYPE_ARROW;}
};