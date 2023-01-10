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
	World(): m_entities(make_shared<map<IEntity*,shared_ptr<IEntity>>>()){}

    inline mutex& getMutex(){return m_mutex;}

    inline weak_ptr<Map> getMap(){return m_map;}
    inline void setMap(shared_ptr<Map> map){m_map = map;}

    void setEntity(shared_ptr<IEntity> pEntity);
    weak_ptr<map<IEntity*,shared_ptr<IEntity>>> getEntities(){return m_entities;}
    shared_ptr<vector<weak_ptr<IEntity>>> getEntitiesInBox(Box box);
    bool deleteEntity(weak_ptr<IEntity> pEntity);

    shared_ptr<vector<ISector*>> getMapInBox(Box box){return m_map->getBox(box);}

private:
    shared_ptr<Map> m_map;
    shared_ptr<map<IEntity*,shared_ptr<IEntity>>> m_entities;

    mutex m_mutex;
};
