#pragma once
#include <memory>
#include <array>
#include <vector>
#include "ISector.hpp"
#include "Size.hpp"

class SectorGenerator
{
public:
    enum: char
    {
        SCENE_COUNTRYSIDE_ROAD,
        SCENE_MEADOW,
        SCENE_MOUNTAINS,
        SCENE_COUNT
    };
    static ISector* randomSector(int sceneType);
    static std::vector<ISector*> generateMap(Size size, std::vector<unsigned char> mapTemplate);

private:

    struct SceneConfig
    {
        int index;
        int percentage;
    };
    static const std::vector<SceneConfig> m_sceneConfigurations[];
    static const ISector* m_availableSectors[];

    SectorGenerator();
};
