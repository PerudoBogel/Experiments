#pragma once

#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "EntityTypes.hpp"
#include "IEntity.hpp"

#include <memory>

class IProjectile: public IEntity
{
public:
	enum
	{
		TRAJECTORY_LINEAR
	};

	IProjectile() :
			m_trajectory(TRAJECTORY_LINEAR),
			m_health(1),
			m_maxHealth(1),
			m_damage(1),
			m_attack(1),
			m_defence(1),
			m_range(1),
			m_speed(1),
			m_size(4,4),
			m_position(0,0)
	{
	}
    virtual ~IProjectile(){};

    virtual int getType() = 0;
    
    int m_trajectory;
    int m_health;
    int m_maxHealth;
    int m_damage;
    int m_attack;
    int m_defence;
    int m_range;
	decltype(Coordinates::x) m_speed;
    Coordinates m_position;
    Size m_size;

protected:
};
