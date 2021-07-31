#pragma once

class Random{
public:
    static int get(int range);
private:
    Random();
    static unsigned int m_seed;
};
