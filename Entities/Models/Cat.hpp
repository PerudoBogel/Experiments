#pragma once

#include <ModelBase.hpp>

class Cat : public ModelBase
{
public:

	Cat()
	{
		m_health = 3;
		m_maxHealth = m_health;
		m_memberFractions.addFraction(Fraction::Type::FRACTION_CATS);
		m_speed = 2;
		m_type = MODEL_TYPE_CAT;
        m_size.h = 10;
        m_size.w = 10;
		m_hitbox.updateSize(m_size);
	}
};
