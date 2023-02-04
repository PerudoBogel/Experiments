#pragma once

#include "EntityBase.hpp"
#include "Coordinates.hpp"
#include "Hitbox.hpp"

class IMoveEntity: public EntityBase
{
public:
    IMoveEntity(void):EntityBase(){}
    IMoveEntity(void* pObj):EntityBase(pObj){};
    ~IMoveEntity(void){}

	decltype(Coordinates::x) m_speed;
    int m_moveStrength;
    Coordinates m_position;
    bool m_isCollidable;
    Hitbox m_hitbox;    
};