#include "Scope.hpp"
#include "SFML/Graphics.hpp"
#include <windows.h>
#include <memory>

class Window2d
{
public:

    Window2d() = delete;
    Window2d(std::shared_ptr<Scope> scope, unsigned int xSize, unsigned int ySize);
    ~Window2d();
    void makeWindow();
    bool update();

private:
    struct texture
    {
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        std::string m_fileName;
    };

    static texture m_textures[];
    static texture m_models[];
    static texture m_void;

    std::shared_ptr<Scope> m_pScope;
    sf::RenderWindow SFMLView;
    HINSTANCE m_instance;
    HWND m_window;
    unsigned int m_PW, m_PH, m_CW, m_CH, m_COX, m_COY;

    static bool loadTexture(texture &texture);
    static bool loadTextures();
};
