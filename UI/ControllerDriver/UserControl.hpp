/*
 * UserControl.hpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_USERCONTROL_HPP_
#define UI_CONTROLLER_USERCONTROL_HPP_

#include <windows.h>
#include <map>
#include "MultiButton.hpp"
#include "MouseActions.hpp"
#include "Coordinates.hpp"

using namespace std;

class UserControl{
public:

	enum class KeyAction{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT
	};

	enum class MouseAction{
		MOUSE_CLICK_RIGHT,
		MOUSE_CLICK_LEFT
	};

	enum class WindowAction{
		KEY_QUIT
	};

	using Callback = void (*)(void* pObj);

	static const map<KeyAction,int> m_keyActionLookup;
	static const map<WindowAction,int> m_windowActionLookup;
	
	UserControl();
	void Run();
	void RegisterKeyAction(KeyAction action, Callback callback, void* pObj);
	void RegisterMouseAction(MouseAction action, Callback callback, void* pObj);
	void RegisterWindowAction(WindowAction action, Callback callback, void* pObj);
	Coordinates GetMouseCoordinates();

private:
	class CallbackExe{
	public:
		CallbackExe(){}
		CallbackExe(Callback callback ,void* pObj):m_callback(callback),m_pObj(pObj){}
		void operator()(){m_callback(m_pObj);};
		
	private:
		Callback m_callback;
		void* m_pObj;
	};

    MSG m_message;
    MultiButton m_multibutton;
    MouseActions m_mouseActions;
	Coordinates m_coordinates;

	map<int,CallbackExe> m_registeredKeyActions;
	map<int,CallbackExe> m_registeredWindowActions;
	map<MouseAction,CallbackExe> m_registeredMouseActions;
};



#endif /* UI_CONTROLLER_USERCONTROL_HPP_ */
