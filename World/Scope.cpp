#include "Scope.hpp"

#include <algorithm>
#include <iostream>

namespace
{
inline void updateCooridinate(decltype(Coordinates::x) &coord, int scSize, decltype(Coordinates::x) limit)
{
    if (coord + static_cast<int>(scSize) / 2 >= limit)
        coord = limit - scSize / 2 - 1;
    else if (coord - static_cast<int>(scSize) / 2 < 0)
        coord = scSize / 2;
}
} // namespace

void Scope::UpdateCoordinates()
{
    updateCooridinate(m_position.x, m_size.w, m_pWorld.lock()->getMap().lock()->m_size.w);
    updateCooridinate(m_position.y, m_size.h, m_pWorld.lock()->getMap().lock()->m_size.h);
    m_offset = m_position - Coordinates(m_size.w/2,m_size.h/2);
}

Scope::Scope(weak_ptr<World> world, weak_ptr<IWorldEntity> pTraced):
        m_pWorld(world),
        m_pTraced(pTraced)
{
    update();
}

void Scope::setWorld(weak_ptr<World> world)
{
    m_pWorld = world;
}

void Scope::setPosition(Coordinates position)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    m_position = position;
    UpdateCoordinates();

    update();
}

void Scope::move(Coordinates step)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    m_position += step;
    UpdateCoordinates();

    update();
}

void Scope::setSize(Size size)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    m_size = size;

    update();
}

void Scope::update()
{
    auto pTraced = m_pTraced.lock();
	if(pTraced)
    {
        m_position = *pTraced->m_pPosition;
        UpdateCoordinates();
	}

    m_map.reset();
	m_map = m_pWorld.lock()->getMapInBox(Box(m_size, m_position));
    m_entities.reset();
	m_entities = m_pWorld.lock()->getEntitiesInBox(Box(m_size,m_position));
}
