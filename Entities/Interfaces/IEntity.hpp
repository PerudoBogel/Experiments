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