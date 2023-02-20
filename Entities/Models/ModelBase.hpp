#pragma once

#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "IEntity.hpp"
#include "EntityType.hpp"
#include "Hitbox.hpp"

#include <memory>

using namespace std;

class ModelBase: public IEntity
{
public:
	ModelBase() :
			m_size(25,25),
			m_hitbox(m_size)
	{}
    virtual ~ModelBase(){};

    int m_type;
	int m_customData;
    int m_health						= 1;
    int m_maxHealth						= 1;
	bool m_isAlive						= 1;
	bool m_isCollidable					= true;
    int m_damage						= 1;
    int m_attack						= 1;
    int m_defence						= 1;
    int m_range							= 100;
    int m_moveStrength					= 1;
	decltype(Coordinates::x) m_speed	= 1;
	ControllerType m_controller = CONTROL_NONE;
	Fraction m_memberFractions,	m_allyFractions;
    Coordinates m_position;
    Size m_size;
	Hitbox m_hitbox;

    bool getIAttack(IAttackEntity& entity)
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
    bool getIDisplay(IDisplayEntity& entity)
	{
		COPY_TO_ENTITY(m_health);
		COPY_TO_ENTITY(m_maxHealth);
		COPY_TO_ENTITY(m_position);
		COPY_TO_ENTITY(m_size);
		COPY_TO_ENTITY(m_type);
		SET_ENTITY_PTR();
		return true;
	}

    bool getIWorld(IWorldEntity& entity)
	{
		COPY_TO_ENTITY(m_position);
		COPY_TO_ENTITY(m_size);
		COPY_TO_ENTITY(m_type);
		SET_ENTITY_PTR();
		return true;
	}
    bool getIMove(IMoveEntity& entity)
	{
		COPY_TO_ENTITY(m_moveStrength);
		COPY_TO_ENTITY(m_position);
		COPY_TO_ENTITY(m_hitbox);
		COPY_TO_ENTITY(m_speed);
		COPY_TO_ENTITY(m_isCollidable);
		SET_ENTITY_PTR();
		return true;
	}
    bool getIControl(IControlEntity& entity)
	{
		COPY_TO_ENTITY(m_controller);
		COPY_TO_ENTITY(m_customData);
		SET_ENTITY_PTR();
		return true;
	}
    
    void setIAttack(const IAttackEntity& entity)
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
    void setIDisplay(const IDisplayEntity& entity)
	{
		COPY_FROM_ENTITY(m_health);
		COPY_FROM_ENTITY(m_maxHealth);
		COPY_FROM_ENTITY(m_position);
		COPY_FROM_ENTITY(m_size);
		COPY_FROM_ENTITY(m_type);
	}
    void setIWorld(const IWorldEntity& entity)
	{
		COPY_FROM_ENTITY(m_position);
		COPY_FROM_ENTITY(m_size);
		COPY_FROM_ENTITY(m_type);
	}
    void setIMove(const IMoveEntity& entity)
	{
		COPY_FROM_ENTITY(m_moveStrength);
		COPY_FROM_ENTITY(m_position);
		COPY_FROM_ENTITY(m_hitbox);
		COPY_FROM_ENTITY(m_speed);
	}
    void setIControl(const IControlEntity& entity)
	{
		COPY_FROM_ENTITY(m_controller);
		COPY_FROM_ENTITY(m_customData);
	}
};
