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
	{UserControl::KeyAction::KEY_UP, 	VK_UP},
	{UserControl::KeyAction::KEY_DOWN, 	VK_DOWN},
	{UserControl::KeyAction::KEY_LEFT, 	VK_LEFT},
	{UserControl::KeyAction::KEY_RIGHT, VK_RIGHT}
};

const map<UserControl::WindowAction,int> UserControl::m_windowActionLookup = 
{
	{UserControl::WindowAction::KEY_QUIT, 	WM_QUIT}
};

UserControl::UserControl()
{
	m_message.message = static_cast<UINT>(~WM_QUIT);
}

void UserControl::Run()
{
	while (PeekMessage(&m_message, NULL, 0, 0, PM_REMOVE))
	{
		
		// If a message was waiting in the message queue, process it
		TranslateMessage(&m_message);
		DispatchMessage(&m_message);

		if (m_message.message == WM_KEYDOWN || m_message.message == WM_KEYUP)
			m_multibutton.registerMsg(m_message);

		try{
			m_coordinates = Coordinates(GET_X_LPARAM(m_message.lParam), GET_Y_LPARAM(m_message.lParam));
			m_registeredWindowActions.at(m_message.message)();
		}catch(const out_of_range data){(void)data;}

		try{
			if (m_mouseActions.isLeftClickDone(m_message))
			{
				m_coordinates = Coordinates(GET_X_LPARAM(m_message.lParam), GET_Y_LPARAM(m_message.lParam));
				m_registeredMouseActions.at(MouseAction::MOUSE_CLICK_LEFT)();
			}
		}catch(const out_of_range data){(void)data;}
		
		try{
			if (m_mouseActions.isRigthClickDone(m_message))
			{
				m_coordinates = Coordinates(GET_X_LPARAM(m_message.lParam), GET_Y_LPARAM(m_message.lParam));
				m_registeredMouseActions.at(MouseAction::MOUSE_CLICK_RIGHT)();
			}
		}catch(const out_of_range data){(void)data;}
	}
	
	if (!m_multibutton.get().empty())
	{
		for (auto button : m_multibutton.get())
		{
			if(button != 0)
			{
				try{
					m_registeredKeyActions.at(button)();
				}catch(const out_of_range data){(void)data;}
			}
		}
	}
}

Coordinates UserControl::GetMouseCoordinates(){
	return m_coordinates;
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
	m_registeredMouseActions[action] = CallbackExe(callback ,pObj);
}