#pragma once

#include "IBaseEntity.hpp"

enum ControllerType
{
	CONTROL_PLAYER,
	CONTROL_AI,
    CONTROL_PROJECTILE,
	CONTROL_NONE
};

class IControlEntity: public IBaseEntity
{
public:
    ControllerType m_controller;
    int m_customData;
};