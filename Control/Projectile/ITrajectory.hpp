#pragma once
#include "Coordinates.hpp"

class ITrajectory
{
public:
    virtual ~ITrajectory(){}

    virtual Coordinates makeStep() = 0;

    virtual bool ifInRange() = 0;
};