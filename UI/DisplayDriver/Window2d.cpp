#include "Window2d.hpp"

namespace
{

LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
        // Quit when we close the main window
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(handle, message, wParam, lParam);
}

}; // namespace

Window2d::Window2d(Size size) :m_PW(static_cast<int>(size.w)), m_PH(static_cast<int>(size.h))
{
    HINSTANCE m_instance = GetModuleHandle(NULL);

    WNDCLASS windowClass;
    windowClass.style = 0;
    windowClass.lpfnWndProc = &onEvent;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = m_instance;
    windowClass.hIcon = NULL;
    windowClass.hCursor = 0;
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = TEXT("SFML App");
    RegisterClass(&windowClass);

    HWND m_window = CreateWindow(TEXT("SFML App"), TEXT("SFML Win32"), WS_SYSMENU | WS_VISIBLE,
                                 0, 0,
                                 m_PW,
                                 m_PH,
                                 NULL, NULL, m_instance, NULL);

    HWND view1 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE,
                              0, 0, m_PW, m_PH, m_window, NULL, m_instance, NULL);

    m_display.create(view1);

    update();
}

Window2d::~Window2d()
{

    // Close our SFML views before destroying the underlying window
    m_display.close();

    // Destroy the main window (all its child controls will be destroyed)
    DestroyWindow(m_window);

    // Don't forget to unregister the window class
    UnregisterClass(TEXT("SFML App"), m_instance);
}

bool Window2d::update()
{
    if(m_frameReady)
    {
        m_display.display();
        m_frameReady = false;
    }

    return true;
}

void Window2d::clear()
{
    m_display.clear();
    m_frameReady = false;
}

void Window2d::addSprites(vector<sf::Sprite>& sprites)
{
    for(auto sprite : sprites)
    {
        m_display.draw(sprite);
    }
}

void Window2d::lock()
{
    m_frameReady = true;
}