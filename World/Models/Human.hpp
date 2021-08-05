#pragma once
#include "IModel.hpp"
class Human: public IModel{
public:
	Human()
	{
		m_moveStrength = 2;
		m_damage = 1;
		m_range = 10;
		m_health = 10;
		m_speed = 20;
	}
	~Human()
	{
	}

    int getType()override{return TYPE_HUMAN;}

};
