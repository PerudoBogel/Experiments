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

	void UpdateController(ControllerType controller)
	{
		m_data.m_controller = controller;
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

	friend std::ostream& operator<< (std::ostream& stream, Entity &entity)
	{
		stream << "Entity id: " << &entity << std::endl;
		stream << "health: " << entity.m_data.m_health << "/" << entity.m_data.m_maxHealth; 
		stream << ", alive: " << entity.m_data.m_isAlive << ", colladible: " << entity.m_data.m_isCollidable << std::endl;
		stream << "attack: " << entity.m_data.m_attack << ", defence: " << entity.m_data.m_defence;
		stream << ", base damage: " << entity.m_data.m_baseDamage << std::endl;
		stream << "range: " << entity.m_data.m_range << ", moveStr: " << entity.m_data.m_moveStrength;
		stream << ", speed: " << entity.m_data.m_speed << std::endl;
		stream << "position: " << entity.m_data.m_position << ", size: " << entity.m_data.m_size << std::endl;

		return stream;
	}

private:

    bool getInterface(IAttackEntity& entity)
	{
		COPY_TO_ENTITY(m_allyFractions);
		COPY_TO_ENTITY(m_attack);
		COPY_TO_ENTITY(m_baseDamage);
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
		COPY_TO_ENTITY(m_textureId);
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
		COPY_FROM_ENTITY(m_baseDamage);
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
		COPY_FROM_ENTITY(m_textureId);
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