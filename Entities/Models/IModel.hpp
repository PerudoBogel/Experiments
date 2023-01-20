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
		m_pIAttack->m_pAllyFractions = &m_allyFractions;
		m_pIAttack->m_pAttack = &m_attack;
		m_pIAttack->m_pDamage = &m_damage;
		m_pIAttack->m_pDefence = &m_attack;
		m_pIAttack->m_pHealth = &m_health;
		m_pIAttack->m_pMemberFractions = &m_memberFractions;
		m_pIAttack->m_pPosition = &m_position;
		m_pIAttack->m_pRange = &m_range;

		m_pIDisplay->m_pHealth = &m_health;
		m_pIDisplay->m_pMaxHealth = &m_maxHealth;
		m_pIDisplay->m_pPosition = &m_position;
		m_pIDisplay->m_pSize = &m_size;
		m_pIDisplay->m_pType = &m_type;
		
		m_pIWorld->m_pPosition = &m_position;
		m_pIWorld->m_pSize = &m_size;
		m_pIWorld->m_pType = &m_type;

		m_pIMove->m_pMoveStrength = &m_moveStrength;
		m_pIMove->m_pPosition = &m_position;
		m_pIMove->m_pSize = &m_size;
		m_pIMove->m_pSpeed = &m_speed;

		m_pIControl->m_controller = CONTROL_NONE;
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
	
protected:
    IAttackEntity 	m_IAttack;
    IDisplayEntity 	m_IDisplay;
    IWorldEntity 	m_IWorld;
    IMoveEntity		m_IMove;
    IControlEntity 	m_IControl;

    IAttackEntity  	*m_pIAttack		=	&m_IAttack;
    IDisplayEntity	*m_pIDisplay	=	&m_IDisplay;
    IWorldEntity	*m_pIWorld		=	&m_IWorld;
    IMoveEntity		*m_pIMove		=	&m_IMove;
    IControlEntity	*m_pIControl	=	&m_IControl;
};
