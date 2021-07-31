#pragma once

#include "ISector.hpp"

class Rock: public ISector{
public:

    int getType(){return TYPE_ROCK;}

private:
};

