#pragma once
#include "Entity.hpp"
#include <map>

class EntityFactory
{
public:
    static EntityFactory *GetInstance();
    std::shared_ptr<Entity> getEntity(int entityId);
private:
    EntityFactory();
    static std::map<int, EntityData> m_entitiesInfo;
    static EntityFactory *m_pInstance;
};