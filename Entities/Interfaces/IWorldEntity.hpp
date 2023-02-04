#pragma once

#include "EntityBase.hpp"
#include "Coordinates.hpp"
#include "Size.hpp"

class IWorldEntity: public EntityBase
{
public:
    IWorldEntity(void):EntityBase(){}
    IWorldEntity(void* pObj):EntityBase(pObj){};
    ~IWorldEntity(void){}

    int m_type; 
    Coordinates m_position;
    Size m_size;
};
