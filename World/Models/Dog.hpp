#pragma once

#include <IModel.hpp>

class Dog : public IModel
{
public:

	Dog()
	{
		m_moveStrength = 1;
		m_health = 6;
		m_maxHealth = m_health;
		m_memberFractions.addFraction(Fraction::Type::FRACTION_DOGS);
	}
	~Dog()
	{
	}

    int getType()override{return MODEL_TYPE_DOG;}

};
