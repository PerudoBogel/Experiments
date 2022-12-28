#pragma once
#include "IModel.hpp"
#include "IProjectile.hpp"
#include "Fraction.hpp"

class AttackModel{
public:
    AttackModel(IModel &model):
    m_pHealth(&model.m_health),
    m_pRange(&model.m_range),
    m_pDefence(&model.m_defence),
    m_pAttack(&model.m_attack),
    m_pAllyFractions(&model.m_allyFractions),
    m_pMemberFractions(&model.m_memberFractions),
    m_pPosition(&model.m_position),
    m_pObj(&model)
    {}

    AttackModel(IProjectile &model):
    m_pHealth(&model.m_health),
    m_pRange(nullptr),
    m_pDefence(nullptr),
    m_pAttack(&model.m_attack),
    m_pAllyFractions(nullptr),
    m_pMemberFractions(nullptr),
    m_pPosition(nullptr),
    m_pObj(&model)
    {}

    bool operator==(const AttackModel &attackModel){
        return m_pObj == attackModel.m_pObj;
    }

    int *m_pHealth;
    int *m_pRange;
    int *m_pDefence;
    int *m_pAttack;
    int *m_pDamage;
    Fraction *m_pAllyFractions, *m_pMemberFractions;
    Coordinates *m_pPosition;
    void *m_pObj;

private:
    AttackModel() = delete;
};