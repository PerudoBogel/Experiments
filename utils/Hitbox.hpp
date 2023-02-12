#pragma once

#include "Coordinates.hpp"
#include "Size.hpp"
#include "Box.hpp"

class Hitbox
{
public:
    Hitbox():
    m_pPostion(nullptr),
    m_psize(nullptr)
    {}
    Hitbox(Coordinates *pPosition, Size *pSize):
    m_hitbox(*pSize, *pPosition),
    m_pPostion(pPosition),
    m_psize(pSize)
    {}
    
    Hitbox& operator=(const Hitbox& hitbox)
    {   
        m_hitbox = hitbox.m_hitbox;
        m_pPostion = hitbox.m_pPostion;
        m_psize = hitbox.m_psize;
        return *this;
    }

    void update()
    {
        m_hitbox.calculate(*m_psize, *m_pPostion);
    }

    bool isCollision(Hitbox &testHitbox)
    {
        return m_hitbox.isCollision(testHitbox.m_hitbox);
    }
    
	bool Contains(const Coordinates &coordinates)
    {
        return m_hitbox.Contains(coordinates);
    }

private:

    Box m_hitbox;
    Coordinates *m_pPostion;
    Size *m_psize;
};