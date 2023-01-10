#pragma once
#include "IModel.hpp"
class Human: public IModel{
public:
	Human()
	{
		m_moveStrength = 2;
		m_damage = 1;
		m_attack = 1000;
		m_range = 25;
		m_health = 10;
		m_maxHealth = m_health;
		m_speed = 2;
		m_memberFractions.addFraction(Fraction::Type::FRACTION_HUMANS);
		m_type = MODEL_TYPE_HUMAN;
	}
};
