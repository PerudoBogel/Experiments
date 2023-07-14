#pragma once

#include "IBaseEntity.hpp"
#include "ControllerType.hpp"

class IControlEntity: public IBaseEntity
{
public:
    ControllerType m_controller;
    int m_customData;
};