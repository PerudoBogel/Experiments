#include "SectorGenerator.hpp"
#include "../../utils/Random.hpp"

#include "Grass.hpp"
#include "Dirt.hpp"
#include "Rock.hpp"

const Grass grass;
const Dirt dirt;
const Rock rock;

const std::vector<SectorGenerator::SceneConfig> SectorGenerator::m_sceneConfigurations[] = {
    [SCENE_COUNTRYSIDE_ROAD] = {{ISector::TYPE_GRASS, 80}, {ISector::TYPE_DIRT, 9900}, {ISector::TYPE_ROCK, 20}},
    [SCENE_MEADOW] = {{ISector::TYPE_GRASS, 9680}, {ISector::TYPE_DIRT, 300}, {ISector::TYPE_ROCK, 20}},
    [SCENE_MOUNTAINS] = {{ISector::TYPE_GRASS, 1000}, {ISector::TYPE_DIRT, 1000}, {ISector::TYPE_ROCK, 8000}}
};

const ISector* SectorGenerator::m_availableSectors[] = {
    [ISector::TYPE_GRASS] = &grass,
    [ISector::TYPE_DIRT] = &dirt,
    [ISector::TYPE_ROCK] = &rock,
};

ISector* SectorGenerator::randomSector(int sceneType)
{
    ISector* randSector;

    int probability = 0, selection = Random::get(10000);

    for (int i = 0; i < ISector::TYPE_COUNT; i++)
    {
        for (auto sceneConf : m_sceneConfigurations[sceneType])
            if (sceneConf.index == i)
            {
                probability += sceneConf.percentage;
                break;
            }

        if (selection <= probability)
        {
            randSector = const_cast<ISector*>(m_availableSectors[i]);
            break;
        }
    }

    return randSector;
}

std::vector<ISector*> SectorGenerator::generateMap(Size size, std::vector<unsigned char> mapTemplate){
	std::vector<ISector*> map;

	for (auto templ : mapTemplate)
		if (templ != 255)
			map.push_back(SectorGenerator::randomSector(templ));
		else
			map.push_back(nullptr);

	return map;
}
