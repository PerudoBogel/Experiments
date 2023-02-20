#pragma once

#include <ModelBase.hpp>

class Dog : public ModelBase
{
public:

	Dog()
	{
		m_moveStrength = 1;
		m_health = 6;
		m_maxHealth = m_health;
		m_memberFractions.addFraction(Fraction::Type::FRACTION_DOGS);
		m_speed = 1;
		m_type = MODEL_TYPE_DOG;
        m_size.h = 15;
        m_size.w = 15;
		m_hitbox.updateSize(m_size);
	}
};
