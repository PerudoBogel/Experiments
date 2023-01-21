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
    
    int *m_pType                = nullptr; 
    int *m_pHealth              = nullptr;
    int *m_pMaxHealth           = nullptr;
    Coordinates *m_pPosition    = nullptr;
    Size *m_pSize               = nullptr;

    int m_frameNo;
    int m_frameCount;
};