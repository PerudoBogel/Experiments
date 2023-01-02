#pragma once

#include "IAttackEntity.hpp"
#include "IDisplayEntity.hpp"
#include "IWorldEntity.hpp"

#include <memory>

using namespace std;

class IEntity
{
public:

    virtual weak_ptr<IAttackEntity> getIAttack(){return m_pIAttack;}
    virtual weak_ptr<IDisplayEntity> getIDisplay(){return m_pIDisplay;}
    virtual weak_ptr<IWorldEntity> getIWorld(){return m_pIWorld;}

protected:
    shared_ptr<IAttackEntity> m_pIAttack;
    shared_ptr<IDisplayEntity> m_pIDisplay;
    shared_ptr<IWorldEntity> m_pIWorld;
};