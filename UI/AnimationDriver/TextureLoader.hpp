#pragma once
#include "TextureConfig.hpp"

#include <string>

class TextureLoader
{
public:
    bool ReadTexture(std::string filename, int id);
    TextureConfig *GetTextureConfig(int id);

private:
    std::map<int, TextureConfig> m_configMap;

    void loadModeInfo(int id, sf::Image &image);
    void updateAltProbablitities(TextureConfig::ModeInfo &modeInfo, std::map<int, int> &probabilityGrad);
};