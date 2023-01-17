#include "Window2d.hpp"
#include "Debug.hpp"

Window2d::Window2d(Size size) :
m_PW(static_cast<int>(size.w)), 
m_PH(static_cast<int>(size.h)),
m_display(sf::VideoMode(size.w, size.h), "My window")
{
  
    m_display.display();
    m_display.setActive();
}

Window2d::~Window2d()
{
    m_display.close();
}

void Window2d::addSprites(vector<sf::Sprite>& sprites)
{
    m_display.clear();
    for(auto sprite : sprites)
    {
        m_display.draw(sprite);
    }
    m_display.display();
}