#pragma once

#include "EntityBase.hpp"
#include "ControllerType.hpp"

class IControlEntity: public EntityBase
{
public:
    IControlEntity(void* pObj):EntityBase(pObj){};
    
    ControllerType m_controller = CONTROL_NONE;
    int m_customData = -1;
};