#pragma once

#include "Coordinates.hpp"
#include "Box.hpp"
#include "IBaseEntity.hpp"

class IDisplayEntity: public IBaseEntity
{
public:    
    int m_type; 
    int m_health;
    int m_maxHealth;
    Coordinates m_position;
    Size m_size;

    int m_frameNo;
    int m_frameCount;
};