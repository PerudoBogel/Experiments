#pragma once

#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "IEntity.hpp"
#include "EntityType.hpp"

#include <memory>

using namespace std;

class ModelBase: public IEntity
{
public:
	ModelBase() :
			m_health(1),
			m_maxHealth(1),
			m_damage(1),
			m_attack(1),
			m_defence(1),
			m_range(1),
			m_memberFractions(),
			m_allyFractions(),
			m_speed(1),
			m_moveStrength(0),
			m_size(25,25),
			m_position(0,0),
			m_hitbox(m_position,m_size)
	{

		m_IDisplay.m_pHealth = &m_health;
		m_IDisplay.m_pMaxHealth = &m_maxHealth;
		m_IDisplay.m_pPosition = &m_position;
		m_IDisplay.m_pSize = &m_size;
		m_IDisplay.m_pType = &m_type;
		
		m_IWorld.m_pPosition = &m_position;
		m_IWorld.m_pSize = &m_size;
		m_IWorld.m_pType = &m_type;

		m_IMove.m_pMoveStrength = &m_moveStrength;
		m_IMove.m_pPosition = &m_position;
		m_IMove.m_pHitbox = &m_hitbox;
		m_IMove.m_pSpeed = &m_speed;

		m_IControl.m_controller = CONTROL_NONE;
	}
    virtual ~ModelBase(){};

    int m_type;

    int m_health;
    int m_maxHealth;
	bool m_isAlive;

    int m_damage;
    int m_attack;
    int m_defence;
    int m_range;
	Fraction m_memberFractions,	m_allyFractions;

	decltype(Coordinates::x) m_speed;
    int m_moveStrength;
    Coordinates m_position;
    Size m_size;
	Hitbox m_hitbox;
	
	#define COPY_TO_ENTITY(varName) entity.varName = varName

    virtual bool getIAttack(IAttackEntity& entity)
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
		return true;
	}
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
