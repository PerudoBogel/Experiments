#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include "TextureMode.hpp"
#include "TextureConfig.hpp"

#include <memory>

class AnimationDriver
{
public:
    AnimationDriver(weak_ptr<Entity> pEntity, TextureConfig &config);

    sf::Sprite *GetFrame(TextureMode mode, float animationTime, int animationFps);
    bool isAlive(){return m_pEntity.lock() != nullptr;}

private:

    struct 
    {
        TextureMode m_mode;
        float m_frameNo;
        int m_altTextureId;
        int m_frameCount;
    } m_frameInfo;

    weak_ptr<Entity> m_pEntity;
    TextureConfig &m_config;
    sf::Sprite m_sprite;

    void ChooseAltTexture(TextureMode mode);
};