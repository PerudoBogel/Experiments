#pragma once

#include "Coordinates.hpp"
#include "Size.hpp"
#include "IBaseEntity.hpp"

class IWorldEntity: public IBaseEntity
{
public:
    int m_type;
    Coordinates m_position;
    Size m_size;
};
