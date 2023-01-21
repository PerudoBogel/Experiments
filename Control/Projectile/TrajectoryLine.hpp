#pragma once

#include "ITrajectory.hpp"

class TrajectoryLine: public ITrajectory
{
public:
    TrajectoryLine() = delete;
    TrajectoryLine(Coordinates start, decltype(Coordinates::x) speed, int range):
    m_speed(speed),m_lastPoint(start),m_range(range),m_pathLength(0)
    {
        m_phiRad = start.phi * PI / 180.0;
    }

    ~TrajectoryLine(){};

    Coordinates makeStep()
    {
        Coordinates step = Coordinates(m_speed * cosf(m_phiRad), m_speed * sinf(m_phiRad));

        m_lastPoint += step;
        m_pathLength += m_speed;

        return step;
    }

    bool ifInRange()
    {
        return m_range > m_pathLength;
    }

private:
    decltype(Coordinates::x) m_speed;
    Coordinates m_lastPoint;
    int m_range,m_pathLength;
    float m_phiRad;
};