#pragma once

#include "IAttackEntity.hpp"
#include "IDisplayEntity.hpp"
#include "IWorldEntity.hpp"
#include "IMoveEntity.hpp"
#include "IControlEntity.hpp"

#include <memory>

using namespace std;

#define COPY_TO_ENTITY(varName) entity.varName = varName
#define COPY_FROM_ENTITY(varName) varName = entity.varName
#define SET_ENTITY_PTR() entity.m_pEntity = this

class IEntity
{
public:

    IEntity(){}
    virtual ~IEntity(){}

    virtual bool getIAttack(IAttackEntity& entity){return false;}
    virtual bool getIDisplay(IDisplayEntity& entity){return false;}
    virtual bool getIWorld(IWorldEntity& entity){return false;}
    virtual bool getIMove(IMoveEntity& entity){return false;}
    virtual bool getIControl(IControlEntity& entity){return false;}
    
    virtual void setIAttack(const IAttackEntity& entity){}
    virtual void setIDisplay(const IDisplayEntity& entity){}
    virtual void setIWorld(const IWorldEntity& entity){}
    virtual void setIMove(const IMoveEntity& entity){}
    virtual void setIControl(const IControlEntity& entity){}
};