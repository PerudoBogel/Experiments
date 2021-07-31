#pragma once

#include "../../utils/Size.hpp"
#include "../../utils/Coordinates.hpp"
#include "../Models/Fraction.hpp"

class IModel
{
public:
    enum
    {
        TYPE_DOG,
        TYPE_HUMAN,
        TYPE_CAT,
        TYPE_COUNT
    };

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
			m_speed(15.0f),
			m_size(15,15)
	{
	}
    virtual ~IModel(){};

    virtual int getType() = 0;
    
    void setCoordinates(Coordinates position)
    {
        m_position = position;
    }

    virtual int move(Coordinates step){
        m_position += step;
        return 1;
    }

    inline Coordinates getPosition()const{return m_position;}
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
	float m_speed;

protected:
    Coordinates m_position;
    Size m_size;
};
