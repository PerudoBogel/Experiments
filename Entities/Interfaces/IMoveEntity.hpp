#pragma once

#include "Coordinates.hpp"
#include "Hitbox.hpp"
#include "IBaseEntity.hpp"

class IMoveEntity: public IBaseEntity
{
public:
	decltype(Coordinates::x) m_speed;
    int m_moveStrength;
    Coordinates m_position;
    bool m_isCollidable;
    Hitbox m_hitbox;
    Size m_size;
};