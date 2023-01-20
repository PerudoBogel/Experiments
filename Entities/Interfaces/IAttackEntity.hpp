#pragma once

#include "EntityBase.hpp"
#include "Fraction.hpp"
#include "Coordinates.hpp"

class IAttackEntity: public EntityBase
{
public:
    IAttackEntity(void* pObj):EntityBase(pObj){};
    
    int *m_pHealth                  = nullptr;
    int *m_pRange                   = nullptr;
    int *m_pDefence                 = nullptr;
    int *m_pAttack                  = nullptr;
    int *m_pDamage                  = nullptr;
    bool m_isAlive                  = true;
    Fraction *m_pAllyFractions      = nullptr; 
    Fraction *m_pMemberFractions    = nullptr;
    Coordinates *m_pPosition        = nullptr;
};