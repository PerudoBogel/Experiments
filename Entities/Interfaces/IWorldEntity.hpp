#pragma once

#include "EntityBase.hpp"
#include "Coordinates.hpp"
#include "Size.hpp"

class IWorldEntity: public EntityBase
{
public:
    IWorldEntity(void* pObj):EntityBase(pObj){};

    int *m_pType                        = nullptr; 
    Coordinates *m_pPosition            = nullptr;
    Size *m_pSize                       = nullptr;
};
