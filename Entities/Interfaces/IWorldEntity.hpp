#pragma once

#include "IEntityBase.hpp"
#include "Coordinates.hpp"
#include "Size.hpp"

class IWorldEntity: public IEntityBase
{
public:

    int *m_pControl                     = nullptr;
    int *m_pType                        = nullptr; 
	decltype(Coordinates::x) *m_pSpeed  = nullptr;
    int *m_pMoveStrength                = nullptr;
    Coordinates *m_pPosition            = nullptr;
    Size *m_pSize                       = nullptr;
};
