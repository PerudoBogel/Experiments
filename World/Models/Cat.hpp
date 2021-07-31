#pragma once

#include <IModel.hpp>

class Cat : public IModel
{
public:

	Cat()
	{
		m_health = 3;
	}
	~Cat()
	{
	}

    int getType()override{return TYPE_CAT;}

};
