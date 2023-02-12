#pragma once

#include "Coordinates.hpp"
#include "Size.hpp"
#include "Box.hpp"
#include "SectorGenerator.hpp"
#include "Map.hpp"
#include "ISector.hpp"
#include "IEntity.hpp"

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

    const map<IEntity*,shared_ptr<IEntity>>& getEntities(void) const{return m_entities;}
    shared_ptr<vector<shared_ptr<IEntity>>> getEntitiesInBox(Box box);
    void setEntity(shared_ptr<IEntity> pEntity);
    bool deleteEntity(shared_ptr<IEntity> pEntity);
    void sync();

    shared_ptr<vector<ISector*>> getMapInBox(Box box){return m_map->getBox(box);}

private:
    shared_ptr<Map> m_map;
    map<IEntity*,shared_ptr<IEntity>> m_entities;
    map<IEntity*,shared_ptr<IEntity>> m_deadEntities;
    map<IEntity*,shared_ptr<IEntity>> m_newEntities;


    mutex m_mutex;
};
