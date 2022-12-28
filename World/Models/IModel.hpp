#pragma once

#include <memory>

#include "Size.hpp"
#include "Coordinates.hpp"
#include "Fraction.hpp"
#include "ModelTypes.hpp"

class IModel
{
public:
	enum
	{
		CONTROL_PLAYER,
		CONTROL_AI,
		CONTROL_NONE
	};

	IModel() :
			m_moveStrength(0),
			m_control(CONTROL_NONE),
			m_health(1),
			m_maxHealth(1),
			m_damage(1),
			m_attack(1),
			m_defence(1),
			m_range(1),
			m_enemyFractions(),
			m_memberFractions(),
			m_allyFractions(),
			m_speed(1),
			m_size(15,15),
			m_position(0,0)
	{
	}
    virtual ~IModel(){};

    virtual int getType() = 0;
    
    virtual int move(Coordinates step){
        m_position += step;
        return 1;
    }

    inline Size getSize()const{return m_size;}

    int m_moveStrength;
    int m_control;
    int m_health;
    int m_maxHealth;
    int m_damage;
    int m_attack;
    int m_defence;
    int m_range;
	Fraction m_enemyFractions,
	m_memberFractions,
	m_allyFractions;
	decltype(Coordinates::x) m_speed;
    Coordinates m_position;

protected:
    Size m_size;
};
