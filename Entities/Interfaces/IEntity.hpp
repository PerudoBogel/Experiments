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

    template<typename T>
    static inline bool getInterface(shared_ptr<IEntity> pEntity, T &interfaceEntity)
    {
        bool rValue = false;
        if(pEntity)
        {
            if(pEntity->getInterface(interfaceEntity))
            {
                rValue = true;
            }
        }
        return rValue;
    }
    
    template<typename T>
    static inline void setInterface(shared_ptr<IEntity> pEntity, T &interfaceEntity)
    {
        if(pEntity)
        {
            pEntity->setInterface(interfaceEntity);
        }
    }

protected:

    virtual bool getInterface(IAttackEntity& entity){return false;}
    virtual bool getInterface(IDisplayEntity& entity){return false;}
    virtual bool getInterface(IWorldEntity& entity){return false;}
    virtual bool getInterface(IMoveEntity& entity){return false;}
    virtual bool getInterface(IControlEntity& entity){return false;}
    
    virtual void setInterface(const IAttackEntity& entity){}
    virtual void setInterface(const IDisplayEntity& entity){}
    virtual void setInterface(const IWorldEntity& entity){}
    virtual void setInterface(const IMoveEntity& entity){}
    virtual void setInterface(const IControlEntity& entity){}
};