#include "ctime"
#include "cstdlib"
#include "Random.hpp"

unsigned int Random::m_seed=432643264;

int Random::get(int range){

    int clockval = clock();

    m_seed += clockval * (clockval << 16) + (m_seed<<15) + (m_seed>>12);

    std::srand(m_seed);

    int random = std::rand();

    return random * range / RAND_MAX;
}
