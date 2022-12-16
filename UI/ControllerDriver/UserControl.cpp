/*
 * UserControl.cpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#include "UserControl.hpp"
#include <iostream>
#include <windowsx.h>
#include "Debug.hpp"

UserControl::UserControl(Controller &&pController) :
		m_input(0), m_controller(pController)
{
	m_message.message = static_cast<UINT>(~WM_QUIT);
}

UserControl::Move UserControl::m_moves[] =
{
{ VK_UP,
{ 0, -1 } },
{ VK_DOWN,
{ 0, 1 } },
{ VK_LEFT,
{ -1, 0 } },
{ VK_RIGHT,
{ 1, 0 } } };

int UserControl::run()
{
	int retVal = DONE;
	while (PeekMessage(&m_message, NULL, 0, 0, PM_REMOVE))
	{
		if (m_message.message == WM_QUIT)
		{
			retVal = QUIT;
			break;
		}

		// If a message was waiting in the message queue, process it
		TranslateMessage(&m_message);
		DispatchMessage(&m_message);

		if (m_message.message == WM_KEYDOWN || m_message.message == WM_KEYUP)
			m_multibutton.registerMsg(m_message);
	}

	if (!m_multibutton.get().empty())
	{
		Coordinates step(0, 0);

		for (size_t i = 0; i < sizeof(m_moves) / sizeof(m_moves[0]); i++)
			for (auto button : m_multibutton.get())
				if (m_moves[i].m_symbol == button)
					step += m_moves[i].move;

		if (step != Coordinates(0, 0))
			m_controller.move(step);
	}


	if (m_mouseActions.isRigthClickDone(m_message))
	{
		std::cout<<"mouse right clicked: "<<std::endl;
		std::cout << "x " << GET_X_LPARAM(m_message.lParam)
				<< " y " << GET_Y_LPARAM(m_message.lParam) << std::endl;

		Coordinates target(GET_X_LPARAM(m_message.lParam), GET_Y_LPARAM(m_message.lParam));
		if(m_pOffset)
			target += *m_pOffset;

		DEBUG_DUMP_VAR(target.x);
		DEBUG_DUMP_VAR(target.y);

		m_controller.attack(target);
	}

	return retVal;
}
