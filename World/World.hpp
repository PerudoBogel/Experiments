#pragma once
#include <vector>
#include <memory>
#include <mutex>

#include "Coordinates.hpp"
#include "Size.hpp"
#include "Box.hpp"
#include "SectorGenerator.hpp"
#include "Map.hpp"
#include "IModel.hpp"

class World
{
public:

	World():m_models(std::make_shared<std::vector<std::shared_ptr<IModel>>>()){}

    inline std::mutex& getMutex(){return m_mutex;}

    inline std::shared_ptr<Map> getMap(){return m_map;}
    inline void setMap(std::shared_ptr<Map> map){m_map = map;}

    std::shared_ptr<IModel> getPlayer();
    inline std::shared_ptr<std::vector<std::shared_ptr<IModel>>> getModels(){return m_models;}
    void setModel(std::shared_ptr<IModel> pModel);


    inline std::vector<ISector*> getMapInBox(Box box){return m_map->getBox(box);}
    std::vector<std::shared_ptr<IModel>> getModelsInBox(Box box);

private:
    std::shared_ptr<Map> m_map;
    std::shared_ptr<std::vector<std::shared_ptr<IModel>>> m_models;
    std::shared_ptr<IModel> m_pPlayerModel;

    std::mutex m_mutex;
};
