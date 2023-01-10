#include "ScopeDisplay.hpp"
#include "EntityTypes.hpp"

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

map<int, ScopeDisplay::Texture> ScopeDisplay::m_entityTextures = 
{
    {PROJECTILE_TYPE_ARROW,     {sf::Sprite(), sf::Texture(), "GameResources/Projectiles/Arrow.png" }},
    {MODEL_TYPE_DOG,            {sf::Sprite(), sf::Texture(), "GameResources/Models/Dog.png"        }},
    {MODEL_TYPE_HUMAN,          {sf::Sprite(), sf::Texture(), "GameResources/Models/Human.png"      }},
    {MODEL_TYPE_CAT,            {sf::Sprite(), sf::Texture(), "GameResources/Models/Cat.png"        }}
};
    

ScopeDisplay::Texture ScopeDisplay::m_void = {sf::Sprite(), sf::Texture(), "GameResources/Sector/Void.png"};

ScopeDisplay::ScopeDisplay(std::shared_ptr<Scope> scope) : m_pScope(scope)
{
    loadTextures();
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
    for (size_t i = 0; i < m_entityTextures.size(); i++)
        if (!loadTexture(m_entityTextures[i]))
            return false;

    for (size_t i = 0; i < m_landTextures.size(); i++)
        if (!loadTexture(m_landTextures[i]))
            return false;

    if (!loadTexture(m_void))
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
                m_sprites.push_back(m_void.sprite);
            else if (!lockedMap->at(sectorIndex))
                m_sprites.push_back(m_void.sprite);
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

    for(auto pEntity : *m_pScope->getEntities().lock().get())
	{
        auto displayEntity = pEntity.lock()->getIDisplay().lock();
       
        m_sprites.push_back(m_entityTextures[*displayEntity->m_pType].sprite);

        //set absolute position;
        position = *displayEntity->m_pPosition;
        // set relative position
        position -= m_pScope->getOffset();
        //align texture
        position -= Coordinates(displayEntity->m_pSize->w/2, displayEntity->m_pSize->h/2);
        
		m_sprites.back().setPosition(position.x, position.y);
        m_sprites.back().setRotation(position.phi);

        if(!displayEntity->m_pMaxHealth || !displayEntity->m_pHealth)
        {
            //no health bar needed
        }
        else if(*displayEntity->m_pMaxHealth != *displayEntity->m_pHealth)
        {    
            healthBarData.position = Coordinates(position.x,position.y);
            healthBarData.percentage = (*displayEntity->m_pHealth * 100) / *displayEntity->m_pMaxHealth;
            healthBarData.size = Size(displayEntity->m_pSize->w, displayEntity->m_pSize->h / 5);
            
            m_healthBarData.push_back(healthBarData);
            m_sprites.push_back(makeHealthBar(&m_healthBarData.back()));
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