#pragma once

#include "Size.hpp"
#include "ISector.hpp"
#include "World.hpp"
#include "IWorldEntity.hpp"

#include <vector>
#include <mutex>

using namespace std;

class Scope
{
public:
    Scope() = delete;
    Scope(weak_ptr<World> world, Coordinates position);

    void setWorld(weak_ptr<World> world);
    void update();
    void setPosition(Coordinates position);
    void move(Coordinates step);
    void setSize(Size size);

    void trace(IWorldEntity *pTraced);
	void stopTrace(){ m_isTracing = false;}

    mutex &getMutex() {return m_mutex;}

    const Coordinates &getPosition() const {return m_position;}
    const Coordinates &getOffset() const {return m_offset;}

    const Size &getSize() const {return m_size;}

    weak_ptr<vector<ISector*>> getMap() const {return m_map;}
    weak_ptr<vector<shared_ptr<IEntity>>> getEntities() const {return m_entities;}

private:
    Coordinates m_position;
    Coordinates m_offset;
    mutex m_mutex; 
    Size m_size;
    shared_ptr<vector<ISector*>> m_map;
    shared_ptr<vector<shared_ptr<IEntity>>> m_entities;
    weak_ptr<World> m_pWorld;
    IWorldEntity *m_pTraced;
    bool m_isTracing;

    void UpdateCoordinates();
};
