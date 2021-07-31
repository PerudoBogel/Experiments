#pragma once

#include <IModel.hpp>

class Dog : public IModel
{
public:

	Dog()
	{
		m_moveStrength = 1;
		m_health = 6;
	}
	~Dog()
	{
	}

    int getType()override{return TYPE_DOG;}

};
