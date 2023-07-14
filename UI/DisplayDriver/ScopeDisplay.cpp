#include "ScopeDisplay.hpp"
#include "EntityType.hpp"
#include "FrameTick.hpp"

#include <iostream>
#include <math.h>
#include <Debug.hpp>
#include <memory>

using namespace std;

namespace
{
    sf::Sprite makeHealthBar(void *pObj)
    {
        ScopeDisplay::HealthBarData *pHealthBarData = reinterpret_cast<ScopeDisplay::HealthBarData*>(pObj);

        int heigth = static_cast<int>(pHealthBarData->size.h);
        int width = static_cast<int>(pHealthBarData->size.w);
        auto x = pHealthBarData->position.x;
        auto y = pHealthBarData->position.y;
        auto percentage = pHealthBarData->percentage;
        int currentPrecentage;
        heigth = heigth == 0 ? 1 : heigth;

        pHealthBarData->image.create(width, heigth, sf::Color(sf::Color::Red));

        for (int x_pos = 0; x_pos < width; x_pos++)
        {
            currentPrecentage = (x_pos * 100) / width;
            if (currentPrecentage > percentage)
                break;

            for (int y_pos = 0; y_pos < heigth; y_pos++)
                pHealthBarData->image.setPixel(x_pos, y_pos, sf::Color::Green);
        }

		pHealthBarData->texture.loadFromImage(pHealthBarData->image);
		pHealthBarData->sprite.setTexture(pHealthBarData->texture,true);
		pHealthBarData->sprite.setPosition(x, y - pHealthBarData->image.getSize().y);

        return pHealthBarData->sprite;
    }

}; // namespace

map<int, ScopeDisplay::Texture> ScopeDisplay::m_landTextures = 
{
    {ISector::TYPE_GRASS,   {sf::Sprite(), sf::Texture(), "GameResources/Sector/Grass.png"  }},
    {ISector::TYPE_DIRT,    {sf::Sprite(), sf::Texture(), "GameResources/Sector/Dirt.png"   }},
    {ISector::TYPE_ROCK,    {sf::Sprite(), sf::Texture(), "GameResources/Sector/Rock.png"   }}
};

ScopeDisplay::ScopeDisplay(std::shared_ptr<Scope> scope) : m_pScope(scope)
{
    loadTextures();
    m_TextureLoader.ReadTexture("GameResources/Models/Human.png", EntityType::TEXTURE_ID_HUMAN);
    m_TextureLoader.ReadTexture("GameResources/Models/Dog.png", EntityType::TEXTURE_ID_DOG);
    m_TextureLoader.ReadTexture("GameResources/Models/Cat.png", EntityType::TEXTURE_ID_CAT);
    m_TextureLoader.ReadTexture("GameResources/Projectiles/Orb.png", EntityType::TEXTURE_ID_ORB);
}

bool ScopeDisplay::loadTexture(Texture &texture)
{
	sf::Image image;
	if (image.loadFromFile(texture.fileName))
	{
		image.createMaskFromColor(sf::Color(255,255,255));
		texture.texture.loadFromImage(image);
		texture.sprite.setTexture(texture.texture, true);
	}
    else
        return false;
    return true;
}

bool ScopeDisplay::loadTextures()
{
    for (size_t i = 0; i < m_landTextures.size(); i++)
        if (!loadTexture(m_landTextures[i]))
            return false;

    return true;
}

bool ScopeDisplay::draw_map()
{
    int scopeStartX = m_pScope->getPosition().x - m_pScope->getSize().w / 2;
    int scopeStartY = m_pScope->getPosition().y - m_pScope->getSize().h / 2;

    int scopeStartXAbsoluteRound = floor(scopeStartX / ISector::m_Size.w) * ISector::m_Size.w;
    int scopeStartYAbsoluteRound = floor(scopeStartY / ISector::m_Size.h) * ISector::m_Size.h;
    int scopeEndXAbsoluteRound = ((m_pScope->getPosition().x + m_pScope->getSize().w / 2) / ISector::m_Size.w) * ISector::m_Size.w;
    int scopeEndYAbsoluteRound = ((m_pScope->getPosition().y + m_pScope->getSize().h / 2) / ISector::m_Size.h) * ISector::m_Size.h;

    auto lockedMap = m_pScope->getMap().lock();
    int mapSize = lockedMap->size();
    int mapWidth = m_pScope->getSize().w / ISector::m_Size.w;

    int scopeWidth = (int)(scopeEndXAbsoluteRound - scopeStartXAbsoluteRound) / ISector::m_Size.w;

    if(mapWidth == scopeWidth)
    {
        mapWidth++;
    }

    for (int x = scopeStartXAbsoluteRound, mapX = 0, scope_x = scopeStartXAbsoluteRound - scopeStartX; x < scopeEndXAbsoluteRound; x += ISector::m_Size.w, mapX++, scope_x += ISector::m_Size.w)
        for (int y = scopeStartYAbsoluteRound, mapY = 0, scope_y = scopeStartYAbsoluteRound - scopeStartY; y < scopeEndYAbsoluteRound; y += ISector::m_Size.h, mapY++, scope_y += ISector::m_Size.h)
        {
            int sectorIndex = mapX  + mapY * mapWidth;

            if (sectorIndex >= mapSize || sectorIndex < 0)
                //m_sprites.push_back(m_void.sprite);
                continue;
            else if (!lockedMap->at(sectorIndex))
                //m_sprites.push_back(m_void.sprite);
                continue;
            else
                m_sprites.push_back(m_landTextures[lockedMap->at(sectorIndex)->getType()].sprite);

            m_sprites.back().setPosition(scope_x,scope_y);
        }

    return true;
}

bool ScopeDisplay::draw_entities()
{        
    HealthBarData healthBarData;
    Coordinates position;
    sf::Sprite *pSprite;
    IDisplayEntity displayEntity;

    for(auto usedFlag: m_animationUsed)
    {
        m_animationUsed[usedFlag.first] = false;
    }

    for(auto pEntity : *m_pScope->getEntities().lock().get())
	{
        pSprite = nullptr;

        if(!Entity::getInterface(pEntity, displayEntity))
        {
            continue;
        }

        auto animationIter = m_animations.find(displayEntity.m_pEntity);

        if(animationIter == m_animations.end())
        {
            auto *pConfig = m_TextureLoader.GetTextureConfig(displayEntity.m_type);

            if(pConfig)
            {
                m_animations.insert(std::pair<void*, AnimationDriver>(displayEntity.m_pEntity, AnimationDriver(pEntity, *pConfig)));
                m_animationUsed[displayEntity.m_pEntity] = true;
                animationIter = m_animations.find(displayEntity.m_pEntity);
                pSprite = animationIter->second.GetFrame(TextureMode::IDLE, 0.4, FrameTick::GetIntance()->GetFps());
            }
        }else
        {
            m_animationUsed[displayEntity.m_pEntity] = true;
            pSprite = animationIter->second.GetFrame(TextureMode::IDLE, 0.4, FrameTick::GetIntance()->GetFps());
        }

        if(pSprite)
        {
            m_sprites.push_back(*pSprite);

            //set absolute position;
            position = displayEntity.m_position;
            // set relative position
            position -= m_pScope->getOffset();
            //align texture
            position -= Coordinates(displayEntity.m_size.w/2, displayEntity.m_size.h/2);
        
            m_sprites.back().setPosition(position.x, position.y);
            m_sprites.back().setRotation(position.phi);

            if(displayEntity.m_maxHealth == -1)
            {
                //no health bar needed
            }
            else if(displayEntity.m_maxHealth != displayEntity.m_health)
            {    
                healthBarData.position = Coordinates(position.x,position.y);
                healthBarData.percentage = (displayEntity.m_health * 100) / displayEntity.m_maxHealth;
                healthBarData.size = Size(displayEntity.m_size.w, displayEntity.m_size.h / 5);
                
                m_healthBarData.push_back(healthBarData);
                m_sprites.push_back(makeHealthBar(&m_healthBarData.back()));
            }
        }
    }
    
    for(auto usedFlag: m_animationUsed)
    {
        if(!usedFlag.second)
        {
            m_animations.erase(usedFlag.first);
            m_animationUsed.erase(usedFlag.first);
        }
    }

    return true;
}

vector<sf::Sprite>& ScopeDisplay::getSprites()
{
    m_sprites.clear();
    m_healthBarData.clear();

    draw_map();
    draw_entities();

    return m_sprites;
}