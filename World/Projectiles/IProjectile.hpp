#pragma once

#include <memory>
#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "ProjectileTypes.hpp"

class IProjectile
{
public:
	enum
	{
		CONTROL_PLAYER,
		CONTROL_AI,
		CONTROL_NONE
	};

	IProjectile() :
			m_trajectory(CONTROL_NONE),
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
    
    virtual int move(Coordinates step){
        m_position += step;
        return 1;
    }

    inline Size getSize()const{return m_size;}

    int m_trajectory;
    int m_health;
    int m_maxHealth;
    int m_damage;
    int m_attack;
    int m_defence;
    int m_range;
	decltype(Coordinates::x) m_speed;
    Coordinates m_position;

protected:
    Size m_size;
};
