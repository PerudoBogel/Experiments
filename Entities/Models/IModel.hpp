#pragma once

#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "IEntity.hpp"
#include "EntityTypes.hpp"

#include <memory>

using namespace std;

class IModel: public IEntity
{
public:
	IModel() :
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
			m_position(0,0)
	{
		m_IAttack.m_pAllyFractions = &m_allyFractions;
		m_IAttack.m_pAttack = &m_attack;
		m_IAttack.m_pDamage = &m_damage;
		m_IAttack.m_pDefence = &m_attack;
		m_IAttack.m_pHealth = &m_health;
		m_IAttack.m_pMemberFractions = &m_memberFractions;
		m_IAttack.m_pPosition = &m_position;
		m_IAttack.m_pRange = &m_range;

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
		m_IMove.m_pSize = &m_size;
		m_IMove.m_pSpeed = &m_speed;

		m_IControl.m_controller = CONTROL_NONE;
	}
    virtual ~IModel(){};

    int m_type;

    int m_health;
    int m_maxHealth;

    int m_damage;
    int m_attack;
    int m_defence;
    int m_range;
	Fraction m_memberFractions,	m_allyFractions;

	decltype(Coordinates::x) m_speed;
    int m_moveStrength;
    Coordinates m_position;
    Size m_size;
	
	IAttackEntity& getIAttack(){return m_IAttack;}
    IDisplayEntity&getIDisplay(){return m_IDisplay;}
    IWorldEntity& getIWorld(){return m_IWorld;}
    IMoveEntity& getIMove(){return m_IMove;}
    IControlEntity& getIControl(){return m_IControl;}
	
protected:
    IAttackEntity 	m_IAttack;
    IDisplayEntity 	m_IDisplay;
    IWorldEntity 	m_IWorld;
    IMoveEntity		m_IMove;
    IControlEntity 	m_IControl;
};
