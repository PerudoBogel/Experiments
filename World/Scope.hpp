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
    Scope(weak_ptr<World> world, weak_ptr<IWorldEntity> pTraced);

    void setWorld(weak_ptr<World> world);
    void update();
    void setPosition(Coordinates position);
    void move(Coordinates step);
    void setSize(Size size);

    void trace(weak_ptr<IWorldEntity> pTraced){m_pTraced = pTraced;}
	void stopTrace(){ m_pTraced.reset();}

    mutex &getMutex() { return m_mutex; }

    const Coordinates &getPosition() { return m_position;}
    const Coordinates &getOffset() { return m_offset;}

    const Size &getSize() const { return m_size; }

    weak_ptr<vector<ISector*>> getMap() const { return m_map; }
    weak_ptr<vector<weak_ptr<IEntity>>> getEntities() const { return m_entities; }

private:
    Coordinates m_position;
    Coordinates m_offset;
    mutex m_mutex;
    Size m_size;
    shared_ptr<vector<ISector*>> m_map;
    shared_ptr<vector<weak_ptr<IEntity>>> m_entities;
    weak_ptr<World> m_pWorld;
    weak_ptr<IWorldEntity> m_pTraced;

    void UpdateCoordinates();
};
