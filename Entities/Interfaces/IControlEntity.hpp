#pragma once

#include "IEntityBase.hpp"
#include "ControllerType.hpp"

class IControlEntity: public IEntityBase
{
public:
    ControllerType m_controller = CONTROL_NONE;
    int m_customData = -1;
};