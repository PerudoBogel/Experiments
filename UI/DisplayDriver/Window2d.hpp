#pragma once
#include "SFML/Graphics.hpp"
#include "Size.hpp"
#include <windows.h>
#include <memory>

using namespace std;

class Window2d
{
public:

    Window2d() = delete;
    Window2d(Size size);
    ~Window2d();

    void clear();
    void addSprites(vector<sf::Sprite>& sprites);
    void lock();

    bool update();

private:

    sf::RenderWindow m_display;
    HINSTANCE m_instance;
    HWND m_window;
    unsigned int m_PW, m_PH;
    bool m_frameReady;
};
