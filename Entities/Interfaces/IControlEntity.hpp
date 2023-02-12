#pragma once

#include "ControllerType.hpp"
#include "IBaseEntity.hpp"

class IControlEntity: public IBaseEntity
{
public:
    ControllerType m_controller;
    int m_customData;
};