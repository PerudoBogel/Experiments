#pragma once

#include "IEntityBase.hpp"
#include "Coordinates.hpp"
#include "Size.hpp"

class IWorldEntity: public IEntityBase
{
public:

    int *m_pType                        = nullptr; 
    Coordinates *m_pPosition            = nullptr;
    Size *m_pSize                       = nullptr;
};
