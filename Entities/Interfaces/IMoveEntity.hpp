#pragma once

#include "EntityBase.hpp"
#include "Coordinates.hpp"

class IMoveEntity: public EntityBase
{
public:
    IMoveEntity(void):EntityBase(){}
    IMoveEntity(void* pObj):EntityBase(pObj){};
    ~IMoveEntity(void){}
    
	decltype(Coordinates::x) *m_pSpeed  = nullptr;
    int *m_pMoveStrength                = nullptr;
    Coordinates *m_pPosition            = nullptr;
    bool m_isCollidable                 = true;
    Size *m_pSize                       = nullptr;        
};