#pragma once

#include "Fraction.hpp"
#include "Coordinates.hpp"
#include "Hitbox.hpp"
#include "IBaseEntity.hpp"

class IAttackEntity: public IBaseEntity
{
public:
    int m_health;
    int m_range;
    int m_defence;
    int m_attack;
    int m_baseDamage;
    bool m_isAlive;
    Fraction m_allyFractions; 
    Fraction m_memberFractions;
    Coordinates m_position;
    Hitbox m_hitbox;
};