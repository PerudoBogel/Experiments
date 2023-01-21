/*
 * UserControl.cpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#include "UserControl.hpp"
#include <iostream>
#include <windowsx.h>

const map<UserControl::KeyAction,int> UserControl::m_keyActionLookup = 
{
	{UserControl::KeyAction::KEY_UP, 	sf::Keyboard::Key::Up},
	{UserControl::KeyAction::KEY_DOWN, 	sf::Keyboard::Key::Down},
	{UserControl::KeyAction::KEY_LEFT, 	sf::Keyboard::Key::Left},
	{UserControl::KeyAction::KEY_RIGHT, sf::Keyboard::Key::Right}
};

const map<UserControl::WindowAction,int> UserControl::m_windowActionLookup = 
{
	{UserControl::WindowAction::KEY_QUIT, 	sf::Event::Closed}
};

const map<UserControl::MouseAction,int> UserControl::m_mouseActionLookup=
{
	{UserControl::MouseAction::MOUSE_PRESS_RIGHT,	MouseActions::STATE_R_PRESSED	},
	{UserControl::MouseAction::MOUSE_DOWN_RIGHT,	MouseActions::STATE_R_DOWN		},
	{UserControl::MouseAction::MOUSE_RELEASE_RIGHT,	MouseActions::STATE_R_RELEASED	},
	{UserControl::MouseAction::MOUSE_UP_RIGHT,		MouseActions::STATE_R_UP		},
	{UserControl::MouseAction::MOUSE_PRESS_LEFT,	MouseActions::STATE_L_PRESSED	},
	{UserControl::MouseAction::MOUSE_DOWN_LEFT,		MouseActions::STATE_L_DOWN		},
	{UserControl::MouseAction::MOUSE_RELEASE_LEFT,	MouseActions::STATE_L_RELEASED	},
	{UserControl::MouseAction::MOUSE_UP_LEFT,		MouseActions::STATE_L_UP		}
};

UserControl::UserControl(Window2d* pWindow):
m_pWindow(pWindow)
{}

void UserControl::Run()
{
	m_mouseActions.Run();
	sf::Event event;
	
	while (m_pWindow->m_display.pollEvent(event))
	{
		m_mouseActions.updateEvent(event);
		m_multibutton.updateEvent(event);

		try{
			m_registeredWindowActions.at(event.type)();
		}catch(const out_of_range data){(void)data;}
	}
	
	try{
		m_registeredMouseActions.at(m_mouseActions.m_leftState)();
	}catch(const out_of_range data){(void)data;}
	
	try{
		m_registeredMouseActions.at(m_mouseActions.m_rightState)();
	}catch(const out_of_range data){(void)data;}
	
	for (int i = 0; i < m_multibutton.get().size() && m_multibutton.getPressedCount() > 0; i++)
	{
		if(m_multibutton.get()[i])
		{
			try{
				m_registeredKeyActions.at(i)();
			}catch(const out_of_range data){(void)data;}
		}
	}
}

Coordinates UserControl::GetMouseCoordinates(){
	return Coordinates(m_mouseActions.m_x,m_mouseActions.m_y);
}

void UserControl::RegisterKeyAction(KeyAction action, Callback callback ,void* pObj)
{
	try{
		int key = m_keyActionLookup.at(action);
		m_registeredKeyActions[key] = CallbackExe(callback ,pObj);
	}catch(const out_of_range data){(void)data;}
}

void UserControl::RegisterWindowAction(WindowAction action, Callback callback ,void* pObj)
{
	try{
		int key = m_windowActionLookup.at(action);
		m_registeredWindowActions[key] = CallbackExe(callback ,pObj);
	}catch(const out_of_range data){(void)data;}
}

void UserControl::RegisterMouseAction(MouseAction action, Callback callback, void* pObj)
{
	try{
		int key = m_mouseActionLookup.at(action);
		m_registeredMouseActions[key] = CallbackExe(callback ,pObj);
	}catch(const out_of_range data){(void)data;}
}