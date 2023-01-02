#pragma once

#include "IEntityBase.hpp"
#include "Coordinates.hpp"
#include "Size.hpp"

class IWorldEntity: public IEntityBase
{
public:
	decltype(Coordinates::x) *m_pSpeed  = nullptr;
    int *m_pMoveStrength                = nullptr;
    Coordinates *m_pPosition            = nullptr;
    Size *m_pSize                       = nullptr;
};