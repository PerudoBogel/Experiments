#pragma once

#include "EntityBase.hpp"
#include "ControllerType.hpp"

class IControlEntity: public EntityBase
{
public:
    IControlEntity(void):EntityBase(){}
    IControlEntity(void* pObj):EntityBase(pObj){};
    ~IControlEntity(void){}
    
    ControllerType m_controller = CONTROL_NONE;
    int m_customData = -1;
};