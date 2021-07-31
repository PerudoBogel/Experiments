#pragma once

#include "Size.hpp"

class ISector{
public:

    enum {
        TYPE_GRASS,
        TYPE_DIRT,
        TYPE_ROCK,
        TYPE_COUNT
    };

    virtual int getType() = 0;
    virtual ~ISector(){};

	static const Size m_Size;
};
