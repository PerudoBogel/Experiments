#pragma once

#include "Size.hpp"
#include "ISector.hpp"
#include "World.hpp"

#include <vector>
#include <mutex>

using namespace std;

class Scope
{
public:
    Scope() = delete;
    Scope(weak_ptr<World> world, weak_ptr<Coordinates> pTracedCoordinates);

    void setWorld(weak_ptr<World> world);
    void update();
    void setPosition(Coordinates position);
    void move(Coordinates step);
    void setSize(Size size);

    void trace(weak_ptr<Coordinates> pTracedCoordinates){m_pTracedCoordinates = pTracedCoordinates;}
	void stopTrace(){ m_pTracedCoordinates.reset();}

    inline mutex &getMutex() { return m_mutex; }

    inline const Coordinates &getPosition() { return m_position;}
    inline const Coordinates &getOffset() { return m_offset;}

    inline const Size &getSize() const { return m_size; }

    inline const weak_ptr<vector<ISector*>> getMap() const { return m_map; }
    inline const weak_ptr<vector<weak_ptr<IEntity>>> getEntities() const { return m_entities; }

private:
    Coordinates m_position;
    Coordinates m_offset;
    mutex m_mutex;
    Size m_size;
    shared_ptr<vector<ISector*>> m_map;
    shared_ptr<vector<weak_ptr<IEntity>>> m_entities;
    weak_ptr<World> m_pWorld;
    weak_ptr<Coordinates> m_pTracedCoordinates;

    void UpdateCoordinates();
};
