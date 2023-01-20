#pragma once

#include "IAttackEntity.hpp"
#include "IDisplayEntity.hpp"
#include "IWorldEntity.hpp"
#include "IMoveEntity.hpp"
#include "IControlEntity.hpp"

#include <memory>

using namespace std;

class IEntity
{
public:

    IEntity(){}
    virtual ~IEntity(){}

    virtual IAttackEntity& getIAttack(){return ATTACK_EMPTY;}
    virtual IDisplayEntity& getIDisplay(){return DISPLAY_EMPTY;}
    virtual IWorldEntity& getIWorld(){return WORLD_EMPTY;}
    virtual IMoveEntity& getIMove(){return MOVE_EMPTY;}
    virtual IControlEntity& getIControl(){return CONTROL_EMPTY;}

private:
    static IAttackEntity ATTACK_EMPTY;
    static IDisplayEntity DISPLAY_EMPTY;
    static IWorldEntity WORLD_EMPTY;
    static IMoveEntity MOVE_EMPTY;
    static IControlEntity CONTROL_EMPTY;
};