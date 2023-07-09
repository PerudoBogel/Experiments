#pragma once
#include "SFML/Graphics.hpp"
#include "Size.hpp"
#include "TextureMode.hpp"

struct TextureConfig
{
    using TextureAltId = int;

    struct ModeInfo
    {
        int m_xOffset, m_yOffset;
        std::map<TextureAltId, int> m_altFrameCount;
        std::map<TextureAltId, int> m_altProb;
    };

    Size m_frameSize;
    std::map<TextureMode, ModeInfo> m_modeInfo;
    sf::Texture m_texture;
    sf::IntRect m_focus;
};