#pragma once

#include "IEntityBase.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"

class IDisplayEntity: public IEntityBase
{
public:
    int *m_type         = nullptr; 
    int *m_pHealth      = nullptr;
    int *m_pMaxHealth   = nullptr;

    int m_frameNo;
    int m_frameCount;
};