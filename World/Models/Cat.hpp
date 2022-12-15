#pragma once

#include <IModel.hpp>

class Cat : public IModel
{
public:

	Cat()
	{
		m_health = 3;
		m_maxHealth = m_health * 2;
	}
	~Cat()
	{
	}

    int getType()override{return TYPE_CAT;}

};
