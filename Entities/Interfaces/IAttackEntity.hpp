#pragma once

#include "IEntityBase.hpp"
#include "Fraction.hpp"
#include "Coordinates.hpp"

class IAttackEntity: public IEntityBase
{
public:
    int *m_pHealth                  = nullptr;
    int *m_pRange                   = nullptr;
    int *m_pDefence                 = nullptr;
    int *m_pAttack                  = nullptr;
    int *m_pDamage                  = nullptr;
    Fraction *m_pAllyFractions      = nullptr; 
    Fraction *m_pMemberFractions    = nullptr;
    Coordinates *m_pPosition        = nullptr;
};