#pragma once

#include <IModel.hpp>

class Cat : public IModel
{
public:

	Cat()
	{
		m_health = 3;
		m_maxHealth = m_health;
		m_memberFractions.addFraction(Fraction::Type::FRACTION_CATS);
		m_speed = 2;
	}
	~Cat()
	{
	}

    int getType()override{return MODEL_TYPE_CAT;}

};
