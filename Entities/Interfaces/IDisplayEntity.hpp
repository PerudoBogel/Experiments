#pragma once

#include "EntityBase.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"

class IDisplayEntity: public EntityBase
{
public:
    IDisplayEntity(void):EntityBase(){}
    IDisplayEntity(void* pObj):EntityBase(pObj){};
    ~IDisplayEntity(void){}
    
    int m_type; 
    int m_health;
    int m_maxHealth;
    Coordinates m_position;
    Size m_size;

    int m_frameNo;
    int m_frameCount;
};