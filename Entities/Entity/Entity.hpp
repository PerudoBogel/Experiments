#pragma once
#include "IAttackEntity.hpp"
#include "IDisplayEntity.hpp"
#include "IMoveEntity.hpp"
#include "IControlEntity.hpp"
#include "EntityData.hpp"

#include <memory>

#define COPY_TO_ENTITY(varName) entity.varName = m_data.varName
#define COPY_FROM_ENTITY(varName) m_data.varName = entity.varName
#define SET_ENTITY_PTR() entity.m_pEntity = this

class Entity
{
public:
    void UpdateData(EntityData &data)
    {
        m_data = data;
    }
    
    template<typename T>
    static inline bool getInterface(std::shared_ptr<Entity> pEntity, T &interfaceEntity)
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
    static inline void setInterface(std::shared_ptr<Entity> pEntity, T &interfaceEntity)
    {
        if(pEntity)
        {
            pEntity->setInterface(interfaceEntity);
        }
    }

private:
    bool getInterface(IAttackEntity& entity)
	{
		COPY_TO_ENTITY(m_allyFractions);
		COPY_TO_ENTITY(m_attack);
		COPY_TO_ENTITY(m_damage);
		COPY_TO_ENTITY(m_defence);
		COPY_TO_ENTITY(m_health);
		COPY_TO_ENTITY(m_memberFractions);
		COPY_TO_ENTITY(m_position);
		COPY_TO_ENTITY(m_range);
		COPY_TO_ENTITY(m_hitbox);
		COPY_TO_ENTITY(m_isAlive);
		SET_ENTITY_PTR();
		return true;
	}
    bool getInterface(IDisplayEntity& entity)
	{
		COPY_TO_ENTITY(m_health);
		COPY_TO_ENTITY(m_maxHealth);
		COPY_TO_ENTITY(m_position);
		COPY_TO_ENTITY(m_size);
		COPY_TO_ENTITY(m_type);
		SET_ENTITY_PTR();
		return true;
	}
    bool getInterface(IMoveEntity& entity)
	{
		COPY_TO_ENTITY(m_moveStrength);
		COPY_TO_ENTITY(m_position);
		COPY_TO_ENTITY(m_hitbox);
		COPY_TO_ENTITY(m_speed);
		COPY_TO_ENTITY(m_isCollidable);
		COPY_TO_ENTITY(m_size);
		SET_ENTITY_PTR();
		return true;
	}
    bool getInterface(IControlEntity& entity)
	{
		COPY_TO_ENTITY(m_controller);
		COPY_TO_ENTITY(m_customData);
		SET_ENTITY_PTR();
		return true;
	}
    
    void setInterface(const IAttackEntity& entity)
	{
		COPY_FROM_ENTITY(m_allyFractions);
		COPY_FROM_ENTITY(m_attack);
		COPY_FROM_ENTITY(m_damage);
		COPY_FROM_ENTITY(m_defence);
		COPY_FROM_ENTITY(m_health);
		COPY_FROM_ENTITY(m_memberFractions);
		COPY_FROM_ENTITY(m_position);
		COPY_FROM_ENTITY(m_range);
		COPY_FROM_ENTITY(m_hitbox);
		COPY_FROM_ENTITY(m_isAlive);
	}
    void setInterface(const IDisplayEntity& entity)
	{
		COPY_FROM_ENTITY(m_health);
		COPY_FROM_ENTITY(m_maxHealth);
		COPY_FROM_ENTITY(m_position);
		COPY_FROM_ENTITY(m_size);
		COPY_FROM_ENTITY(m_type);
	}
    void setInterface(const IMoveEntity& entity)
	{
		COPY_FROM_ENTITY(m_moveStrength);
		COPY_FROM_ENTITY(m_position);
		COPY_FROM_ENTITY(m_hitbox);
		COPY_FROM_ENTITY(m_speed);
		COPY_FROM_ENTITY(m_size);
	}
    void setInterface(const IControlEntity& entity)
	{
		COPY_FROM_ENTITY(m_controller);
		COPY_FROM_ENTITY(m_customData);
	}

    EntityData m_data;
};