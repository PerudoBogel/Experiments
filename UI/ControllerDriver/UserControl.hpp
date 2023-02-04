/*
 * UserControl.hpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_USERCONTROL_HPP_
#define UI_CONTROLLER_USERCONTROL_HPP_

#include "MultiButton.hpp"
#include "MouseActions.hpp"
#include "Coordinates.hpp"
#include "Window2d.hpp"

#include <map>
#include <memory>

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
		MOUSE_PRESS_RIGHT,
		MOUSE_DOWN_RIGHT,
		MOUSE_RELEASE_RIGHT,
		MOUSE_UP_RIGHT,
		MOUSE_PRESS_LEFT,
		MOUSE_DOWN_LEFT,
		MOUSE_RELEASE_LEFT,
		MOUSE_UP_LEFT
	};

	enum class WindowAction{
		KEY_QUIT
	};

	using Callback = void (*)(void* pObj);

	static const map<KeyAction,int> m_keyActionLookup;
	static const map<WindowAction,int> m_windowActionLookup;
	static const map<MouseAction,int> m_mouseActionLookup;

	UserControl() = delete;
	UserControl(Window2d* pWindow);
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

    MultiButton m_multibutton;
    MouseActions m_mouseActions;
	Window2d* m_pWindow;

	map<int,CallbackExe> m_registeredKeyActions;
	map<int,CallbackExe> m_registeredWindowActions;
	map<int,CallbackExe> m_registeredMouseActions;
};



#endif /* UI_CONTROLLER_USERCONTROL_HPP_ */
