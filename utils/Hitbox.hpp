#pragma once

#include "Coordinates.hpp"
#include "Size.hpp"
#include "Box.hpp"
#include <iostream>

class Hitbox
{
public:
    Hitbox():
    m_postion(0,0)
    {}

    Hitbox(Size &size):
    m_postion(0,0), 
    m_size1(size.w, size.h*6/10),
    m_size2(size.w* 6/10, size.h),
    m_hitbox1(m_size1, m_postion),
    m_hitbox2(m_size2, m_postion)
    {}
    
    Hitbox& operator=(const Hitbox& hitbox)
    {   
        m_hitbox1 = hitbox.m_hitbox1;
        m_hitbox2 = hitbox.m_hitbox2;
        m_size1 = hitbox.m_size1;
        m_size2 = hitbox.m_size2;
        return *this;
    }

    void update(Size &size)
    {
        m_size1 = Size(size.w, size.h* 6/10);
        m_size2 = Size(size.w* 6/10, size.h);
        update();
    }

    void update()
    {
        m_hitbox1.calculate(m_size1, m_postion);
        m_hitbox2.calculate(m_size2, m_postion);
    }

    void update(Coordinates &postion)
    {
        m_postion = postion;
        update();
    }

    bool isCollision(Hitbox &testHitbox)
    {
        bool rVal[4];

        rVal[0] = m_hitbox1.isCollision(testHitbox.m_hitbox1);
        rVal[1] = m_hitbox2.isCollision(testHitbox.m_hitbox1);
        rVal[2] = m_hitbox1.isCollision(testHitbox.m_hitbox2);
        rVal[3] = m_hitbox2.isCollision(testHitbox.m_hitbox2);

        return rVal[0] | rVal[1] | rVal[2] | rVal[3];
    }
    
	bool Contains(const Coordinates &coordinates)
    {
        bool rVal[2];

        rVal[0] = m_hitbox1.Contains(coordinates);
        rVal[1] = m_hitbox2.Contains(coordinates);

        return rVal[0] | rVal[1];
    }

    friend std::ostream& operator<< (std::ostream& stream, Hitbox &hitbox)
    {
        stream << "hitboxes: {xmin:";
        stream << hitbox.m_hitbox1.Xmin << ", xmax:" << hitbox.m_hitbox1.Xmax << "; ymin:";
        stream << hitbox.m_hitbox1.Ymin << ", ymax:" << hitbox.m_hitbox1.Ymax << "}, {xmax:";
        stream << hitbox.m_hitbox2.Xmin << ", xmax:" << hitbox.m_hitbox2.Xmax << "; ymin:";
        stream << hitbox.m_hitbox2.Ymin << ", ymax:" << hitbox.m_hitbox2.Ymax << "}" << std::endl;
        return stream;
    }

    Coordinates m_postion;
    Size m_size1,m_size2;
    Box m_hitbox1,m_hitbox2;
};