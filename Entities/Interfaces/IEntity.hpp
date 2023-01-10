#pragma once

#include "IAttackEntity.hpp"
#include "IDisplayEntity.hpp"
#include "IWorldEntity.hpp"
#include "IMoveEntity.hpp"
#include "IControlEntity.hpp"

#include <memory>

using namespace std;

class IEntity
{
public:

    IEntity():
	m_pIAttack(make_shared<IAttackEntity>()),
	m_pIDisplay(make_shared<IDisplayEntity>()),
	m_pIWorld(make_shared<IWorldEntity>()),
	m_pIMove(make_shared<IMoveEntity>()),
	m_pIControl(make_shared<IControlEntity>())
    {}

    virtual ~IEntity(){}

    weak_ptr<IAttackEntity> getIAttack(){return m_pIAttack;}
    weak_ptr<IDisplayEntity> getIDisplay(){return m_pIDisplay;}
    weak_ptr<IWorldEntity> getIWorld(){return m_pIWorld;}
    weak_ptr<IMoveEntity> getIMove(){return m_pIMove;}
    weak_ptr<IControlEntity> getIControl(){return m_pIControl;}

protected:
    shared_ptr<IAttackEntity> m_pIAttack;
    shared_ptr<IDisplayEntity> m_pIDisplay;
    shared_ptr<IWorldEntity> m_pIWorld;
    shared_ptr<IMoveEntity> m_pIMove;
    shared_ptr<IControlEntity> m_pIControl;
};