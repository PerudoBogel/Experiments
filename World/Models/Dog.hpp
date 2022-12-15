#pragma once

#include <IModel.hpp>

class Dog : public IModel
{
public:

	Dog()
	{
		m_moveStrength = 1;
		m_health = 6;
		m_maxHealth = m_health * 2;
	}
	~Dog()
	{
	}

    int getType()override{return TYPE_DOG;}

};
