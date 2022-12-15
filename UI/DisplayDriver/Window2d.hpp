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

    struct Element
    {
        sf::Sprite sprite;
        void* pObj;
        sf::Sprite (*pCallback)(void*);
    };

    void clear();
    void addElements(vector<Element>& elements);
    void lock();

    bool update();

private:

    sf::RenderWindow m_display;
    HINSTANCE m_instance;
    HWND m_window;
    unsigned int m_PW, m_PH;
    bool m_frameReady;
};
