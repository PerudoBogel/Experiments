#include "Scope.hpp"
#include "Window2d.hpp"

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

    static Texture m_textures[];
    static Texture m_models[];
    static Texture m_projectiles[];
    static Texture m_void;

    shared_ptr<Scope> m_pScope;
    vector<sf::Sprite> m_sprites;
    vector<HealthBarData> m_healthBarData;

    static bool loadTexture(Texture &texture);
    static bool loadTextures();

    bool draw_map();
    bool draw_entities();
};
