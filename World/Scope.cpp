#include "Scope.hpp"
#include "algorithm"
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

Scope::Scope() :
		m_traceActive(false)
{
}

Scope::Scope(std::shared_ptr<World> world, std::shared_ptr<Coordinates> pModel) :
		m_traceActive(true),
        m_pWorld(world),
        m_pTracedObject(pModel)
{
}

void Scope::setWorld(std::shared_ptr<World> world)
{
    m_pWorld = world;
}

void Scope::trace(std::shared_ptr<Coordinates> pTraceOject)
{
	m_pTracedObject = pTraceOject;
	m_traceActive = true;
}

void Scope::setCoordinates(Coordinates position)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    m_position = position;
    updateCooridinate(m_position.x, m_size.w, m_pWorld->getMap()->m_size.w);
    updateCooridinate(m_position.y, m_size.h, m_pWorld->getMap()->m_size.h);

    update();
}

void Scope::move(Coordinates step)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    m_position += step;
    updateCooridinate(m_position.x, m_size.w, m_pWorld->getMap()->m_size.w);
    updateCooridinate(m_position.y, m_size.h, m_pWorld->getMap()->m_size.h);

    update();
}

void Scope::setSize(Size size)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    m_size = size;
    updateCooridinate(m_position.x, m_size.w, m_pWorld->getMap()->m_size.w);
    updateCooridinate(m_position.y, m_size.h, m_pWorld->getMap()->m_size.h);

    update();
}

void Scope::update()
{
	if(m_traceActive){

        m_position = *m_pTracedObject;
	    updateCooridinate(m_position.x, m_size.w, m_pWorld->getMap()->m_size.w);
	    updateCooridinate(m_position.y, m_size.h, m_pWorld->getMap()->m_size.h);
	}

	m_map = m_pWorld->getMapInBox(Box(m_size, m_position));
	m_models = m_pWorld->getModelsInBox(Box(m_size,m_position));
}
