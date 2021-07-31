#pragma once

#include "ISector.hpp"

class Dirt: public ISector{
public:

    int getType(){return TYPE_DIRT;}

private:
};

