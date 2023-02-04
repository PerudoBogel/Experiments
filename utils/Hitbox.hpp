#pragma once

#include "Coordinates.hpp"
#include "Size.hpp"
#include "Box.hpp"

class Hitbox
{
public:
    Hitbox(Coordinates &position, Size &size):
    m_hitbox(size, position),
    m_postion(position),
    m_size(size)
    {}
    
    Hitbox& operator=(const Hitbox& hitbox)
    {   
        m_hitbox = hitbox.m_hitbox;
        m_postion = hitbox.m_postion;
        m_size = hitbox.m_size;
        return *this;
    }

    void update()
    {
        m_hitbox.calculate(m_size, m_postion);
    }

    bool isCollision(Hitbox &testHitbox)
    {
        return m_hitbox.isCollision(testHitbox.m_hitbox);
    }

private:

    Box m_hitbox;
    Coordinates &m_postion;
    Size &m_size;
};