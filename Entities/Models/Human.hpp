#pragma once
#include "ModelBase.hpp"
class Human: public ModelBase
{
public:
	Human()
	{
		m_moveStrength = 2;
		m_damage = 1;
		m_attack = 1000;
		m_range = 100;
		m_health = 10;
		m_maxHealth = m_health;
		m_speed = 2;
		m_memberFractions.addFraction(Fraction::Type::FRACTION_HUMANS);
		m_type = MODEL_TYPE_HUMAN;
	}
};
