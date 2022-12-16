#pragma once
#include <IModel.hpp>
#include <vector>
#include <mutex>

#include "Size.hpp"
#include "ISector.hpp"
#include "World.hpp"

class Scope
{
public:
    Scope();
    Scope(std::shared_ptr<World> world, Coordinates& pModel);

    void setWorld(std::shared_ptr<World> world);
    void update();
    void setPosition(Coordinates position);
    void move(Coordinates step);
    void setSize(Size size);

    void trace(Coordinates& traceOject);
	void stopTrace(){ m_traceActive = false;}

    inline std::mutex &getMutex() { return m_mutex; }

    inline const Coordinates &getPosition() { return m_position;}
    inline const Coordinates &getOffset() { return m_offset;}

    inline const Size &getSize() const { return m_size; }

    inline const std::vector<ISector*> &getMap() const { return m_map; }
    inline const std::vector<std::shared_ptr<IModel>> &getCharacters() const { return m_models; }

private:
    Coordinates m_position;
    Coordinates m_offset;
    std::mutex m_mutex;
    Size m_size;
    std::vector<ISector*> m_map;
    std::vector<std::shared_ptr<IModel>> m_models;
    std::shared_ptr<World> m_pWorld;
    Coordinates* m_pTracedObject;
    bool m_traceActive;
};
