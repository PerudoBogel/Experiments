#include "AnimationDriver.hpp"
#include "Debug.hpp"

AnimationDriver::AnimationDriver(weak_ptr<IEntity> pEntity, TextureConfig &config):
m_pEntity(pEntity), m_config(config)
{
    IDisplayEntity displayEntity;
    IEntity::getInterface(pEntity.lock(), displayEntity);

    m_frameInfo.m_mode = TextureMode::NONE;
    m_frameInfo.m_frameNo = 0;

    m_config.m_focus.width = m_config.m_frameSize.w;
    m_config.m_focus.height = m_config.m_frameSize.h;
    m_config.m_focus.left = 0;
    m_config.m_focus.top = 1;
    
    m_sprite.setTexture(m_config.m_texture);
    m_sprite.setTextureRect(m_config.m_focus);
    m_sprite.setPosition(sf::Vector2f(50, 50));
    auto xScale = displayEntity.m_size.w/m_config.m_frameSize.w;
    auto yScale = displayEntity.m_size.h/m_config.m_frameSize.h;
    m_sprite.setScale(xScale,yScale);
}

sf::Sprite *AnimationDriver::GetFrame(TextureMode mode, float animationTime, int animationFps)
{
    float nextFrame;
    auto modeInfoIt = m_config.m_modeInfo.find(mode);
    IDisplayEntity displayEntity;

    if(!IEntity::getInterface(m_pEntity.lock(), displayEntity))
    {
        return nullptr;
    }
    else if(modeInfoIt == m_config.m_modeInfo.end())
    {
        return &m_sprite;
    }

    if(mode == m_frameInfo.m_mode)
    {
        nextFrame = m_frameInfo.m_frameNo + m_frameInfo.m_frameCount / animationTime / animationFps;
        
        if(m_frameInfo.m_frameCount <= nextFrame)
        {
            nextFrame = 0;
            ChooseAltTexture(mode);
        }
    }
    else
    {
        nextFrame = 0;
        ChooseAltTexture(mode);
    }

    m_frameInfo.m_frameNo = nextFrame;

    float xOffset = static_cast<int>(m_frameInfo.m_frameNo) * m_config.m_frameSize.w + m_config.m_modeInfo[mode].m_xOffset;
    float yOffset = m_frameInfo.m_altTextureId * m_config.m_frameSize.h + m_config.m_modeInfo[mode].m_yOffset;

    m_config.m_focus.left = xOffset;
    m_config.m_focus.top = yOffset;
    
    m_sprite.setTextureRect(m_config.m_focus);
    auto xScale = displayEntity.m_size.w/m_config.m_frameSize.w;
    auto yScale = displayEntity.m_size.h/m_config.m_frameSize.h;
    m_sprite.setScale(xScale,yScale);
    
    return &m_sprite;
}

void AnimationDriver::ChooseAltTexture(TextureMode mode)
{
    int altId = 0;
    std::srand(m_frameInfo.frameCounter++);
    int randVal = std::rand() / (RAND_MAX / 100);
    
    auto &modeInfo = m_config.m_modeInfo[mode];
    for(auto altIter = modeInfo.m_altProb.begin(); altIter != modeInfo.m_altProb.end(); altIter++)
    {
        if(altIter->second > std::rand() / (RAND_MAX / 100))
        {
            altId = altIter->first;
            break;
        }
    }

    m_frameInfo.m_altTextureId = altId;
    m_frameInfo.m_frameCount = m_config.m_modeInfo[mode].m_altFrameCount[altId];
    m_frameInfo.m_mode = mode;
}