#pragma once

#include "Coordinates.hpp"
#include "Size.hpp"
#include "Box.hpp"
#include "SectorGenerator.hpp"
#include "Map.hpp"
#include "ISector.hpp"
#include "Entity.hpp"

#include <vector>
#include <map>
#include <memory>
#include <mutex>

using namespace std;

class World
{
public:
	World(){}

    inline mutex& getMutex(){return m_mutex;}

    inline weak_ptr<Map> getMap(){return m_map;}
    inline void setMap(shared_ptr<Map> map){m_map = map;}

    const map<Entity*,shared_ptr<Entity>>& getEntities(void) const{return m_entities;}
    shared_ptr<vector<shared_ptr<Entity>>> getEntitiesInBox(Box box);
    void setEntity(shared_ptr<Entity> pEntity);
    bool deleteEntity(shared_ptr<Entity> pEntity);
    void sync();

    shared_ptr<vector<ISector*>> getMapInBox(Box box){return m_map->getBox(box);}

private:
    shared_ptr<Map> m_map;
    map<Entity*,shared_ptr<Entity>> m_entities;
    map<Entity*,shared_ptr<Entity>> m_deadEntities;
    map<Entity*,shared_ptr<Entity>> m_newEntities;


    mutex m_mutex;
};
