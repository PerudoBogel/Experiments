#pragma once
#include "Entity.hpp"

class EntityFactory
{
public:
    EntityFactory() = delete;
    static std::shared_ptr<Entity> getEntity(int entityId);
};