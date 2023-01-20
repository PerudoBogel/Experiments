#pragma once

#include "EntityBase.hpp"
#include "Coordinates.hpp"

class IMoveEntity: public EntityBase
{
public:
    IMoveEntity(void* pObj):EntityBase(pObj){};
    
	decltype(Coordinates::x) *m_pSpeed  = nullptr;
    int *m_pMoveStrength                = nullptr;
    Coordinates *m_pPosition            = nullptr;
    bool m_isCollidable                 = true;
    Size *m_pSize                       = nullptr;        
};