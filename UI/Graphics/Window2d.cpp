#include "Window2d.hpp"
#include <iostream>

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

inline void makeHealthBar(int heigth, int width, int percentage,
		sf::Image &Image)
{
	heigth = heigth == 0 ? 1 : heigth;

	Image.create(width, heigth, sf::Color(sf::Color::Red));

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < heigth; y++)
			Image.setPixel(x, y,
					sf::Color(
							x * 100 / width <= percentage ?
									sf::Color::Green : sf::Color::Red));
		if (x * 100 / width > percentage)
			break;
	}
}

}; // namespace

Window2d::texture Window2d::m_textures[] = {
    [ISector::TYPE_GRASS] = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Sector/Grass.png"},
    [ISector::TYPE_DIRT] = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Sector/Dirt.png"},
    [ISector::TYPE_ROCK] = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Sector/Rock.png"}};

Window2d::texture Window2d::m_models[] = {
    [IModel::TYPE_DOG] = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Models/Dog.png"},
    [IModel::TYPE_HUMAN] = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Models/Human.png"},
    [IModel::TYPE_CAT] = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Models/Cat.png"}};

Window2d::texture Window2d::m_void = {sf::Sprite(), sf::Texture(), "C:/SW/Project/UI/Graphics/Sector/Void.png"};

Window2d::Window2d(std::shared_ptr<Scope> scope, unsigned int xSize, unsigned int ySize) : m_pScope(scope),
                                                                                           m_PW(xSize),
                                                                                           m_PH(ySize)
{
    loadTextures();

    m_pScope->getMutex().lock();
    m_CW = m_pScope->getSize().w;
    m_CH = m_pScope->getSize().h;
    m_pScope->getMutex().unlock();

    m_COX = (m_PW - m_CW) / 2;
    m_COY = (m_PH - m_CH) / 2;
}

Window2d::~Window2d()
{

    // Close our SFML views before destroying the underlying window
    SFMLView.close();

    // Destroy the main window (all its child controls will be destroyed)
    DestroyWindow(m_window);

    // Don't forget to unregister the window class
    UnregisterClass(TEXT("SFML App"), m_instance);
}

bool Window2d::loadTexture(texture &texture)
{
	sf::Image image;
	if (image.loadFromFile(texture.m_fileName))
	{
		image.createMaskFromColor(sf::Color(255,255,255));
		texture.m_texture.loadFromImage(image);
		texture.m_sprite.setTexture(texture.m_texture, true);
	}
    else
        return false;
    return true;
}

bool Window2d::loadTextures()
{
    for (size_t i = 0; i < sizeof(m_models) / sizeof(m_models[0]); i++)
        if (!loadTexture(m_models[i]))
            return false;

    for (size_t i = 0; i < sizeof(m_textures) / sizeof(m_textures[0]); i++)
        if (!loadTexture(m_textures[i]))
            return false;

    if (!loadTexture(m_void))
        return false;

    return true;
}

bool Window2d::update()
{
    if (sizeof(m_textures) == 0)
        return false;

    m_pScope->update();
    SFMLView.clear();

    int landWidth = ISector::m_Size.w;
    int landHeigth = ISector::m_Size.h;
    int scopeXOrigin = (m_pScope->getPosition().x - m_pScope->getSize().w / 2);
    int scopeYOrigin = (m_pScope->getPosition().y - m_pScope->getSize().h / 2);

    sf::Sprite *Sector;
    std::lock_guard<std::mutex> lockGuard(m_pScope->getMutex());

	for (int y = 0; y < m_pScope->getSize().h / landHeigth; y++)
		for (int x = 0; x < m_pScope->getSize().w / landWidth; x++)
		{
			if (x + y * m_pScope->getSize().w / landWidth
					>= static_cast<int>(m_pScope->getMap().size()))
				Sector = &m_void.m_sprite;
			else if (!m_pScope->getMap()[x
					+ y * m_pScope->getSize().w / landWidth])
				Sector = &m_void.m_sprite;
			else
				Sector =
						&m_textures[m_pScope->getMap()[x
								+ y * m_pScope->getSize().w / landWidth]->getType()].m_sprite;

			Sector->setPosition(x * landWidth, y * landHeigth);

			SFMLView.draw(*Sector);
		}
        
    sf::Sprite *Character,HealthBar;
    sf::Texture *CharacterT,HealthBarT;
    sf::Image HealthBarI;
    int x,y;

    for(auto pCharacter : m_pScope->getCharacters())
	{
        Character = &m_models[pCharacter->getType()].m_sprite;
        CharacterT = &m_models[pCharacter->getType()].m_texture;

        //set absolute position;
        x = pCharacter->getPosition().x;
        y = pCharacter->getPosition().y;
        // set relative position
        x -= scopeXOrigin;
        y -= scopeYOrigin;
        //align texture
        x -= ISector::m_Size.w;
        y -= ISector::m_Size.h;

		makeHealthBar(CharacterT->getSize().y / 5, CharacterT->getSize().x,
				pCharacter->m_health * 100 / pCharacter->m_maxHealth,
				HealthBarI);
		HealthBarT.loadFromImage(HealthBarI);
		HealthBar.setTexture(HealthBarT,true);

		Character->setPosition(x, y);
		HealthBar.setPosition(x, y - HealthBarI.getSize().y);

        SFMLView.draw(*Character);
        SFMLView.draw(HealthBar);
    }

    SFMLView.display();

    return true;
}

void Window2d::makeWindow()
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
                              m_COX, m_COY, m_CW, m_CH, m_window, NULL, m_instance, NULL);

    SFMLView.create(view1);

    update();
}
