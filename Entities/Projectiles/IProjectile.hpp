#pragma once

#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "IEntity.hpp"
#include "EntityTypes.hpp"

#include <memory>

class IProjectile: public IEntity
{
public:

	IProjectile() :
			m_damage(1),
			m_attack(1),
			m_defence(1),
			m_range(1),
			m_speed(1),
			m_size(4,4),
			m_position(0,0)
	{
		m_pIAttack->m_pAttack = &m_attack;
		m_pIAttack->m_pDamage = &m_damage;
		m_pIAttack->m_pDefence = &m_attack;
		m_pIAttack->m_pPosition = &m_position;
		m_pIAttack->m_pRange = &m_range;

		m_pIDisplay->m_pPosition = &m_position;
		m_pIDisplay->m_pSize = &m_size;
		m_pIDisplay->m_pType = &m_type;
		
		m_pIWorld->m_pPosition = &m_position;
		m_pIWorld->m_pSize = &m_size;
		m_pIWorld->m_pType = &m_type;
		
		m_pIMove->m_isCollidable = false;
		m_pIMove->m_pPosition = &m_position;
		m_pIMove->m_pSize = &m_size;
		m_pIMove->m_pSpeed = &m_speed;
		
		m_pIControl->m_controller = CONTROL_PROJECTILE;
	}
    virtual ~IProjectile(){};
    
	int m_type;
    int m_damage;
    int m_attack;
    int m_defence;
    int m_range;
	decltype(Coordinates::x) m_speed;
    Coordinates m_position;
    Size m_size;

protected:
};
