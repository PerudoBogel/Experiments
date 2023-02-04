#pragma once

#include "EntityBase.hpp"
#include "Fraction.hpp"
#include "Coordinates.hpp"
#include "Hitbox.hpp"

class IAttackEntity: public EntityBase
{
public:
    IAttackEntity(void):EntityBase(){}
    IAttackEntity(void* pObj):EntityBase(pObj){};
    ~IAttackEntity(void){}
    
    int m_health;
    int m_range;
    int m_defence;
    int m_attack;
    int m_damage;
    bool m_isAlive;
    Fraction m_allyFractions; 
    Fraction m_memberFractions;
    Coordinates m_position;
    Hitbox m_hitbox;
};