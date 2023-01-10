#pragma once

#include "Scope.hpp"
#include "Window2d.hpp"

#include <map>

using namespace std;

class ScopeDisplay
{
public:
    
    struct HealthBarData
    {
        sf::Sprite sprite;
        sf::Image image;
        sf::Texture texture;
        Coordinates position;
        int percentage;
        Size size;
    };

    ScopeDisplay() = delete;
    ScopeDisplay(shared_ptr<Scope> scope);
    vector<sf::Sprite>& getSprites();

private:

    struct Texture
    {
        sf::Sprite sprite;
        sf::Texture texture;
        string fileName;
    };

    static map<int, Texture> m_landTextures;
    static map<int ,Texture> m_entityTextures;
    static Texture m_void;

    shared_ptr<Scope> m_pScope;
    vector<sf::Sprite> m_sprites;
    vector<HealthBarData> m_healthBarData;

    static bool loadTexture(Texture &texture);
    static bool loadTextures();

    bool draw_map();
    bool draw_entities();
};
