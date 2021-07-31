#pragma once

#include "ISector.hpp"

class Grass : public ISector
{
public:
    int getType() { return TYPE_GRASS; }

private:
};
