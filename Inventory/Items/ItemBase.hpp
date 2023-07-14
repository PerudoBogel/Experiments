#pragma once
#include "ItemType.hpp"

class ItemBase
{
public:
    ItemBase(){};
    virtual ~ItemBase(){};

    ItemType GetType(){return m_type;}
    float GetWeight(){return m_weight;}

protected:
    ItemType m_type;
    float m_weight;
};