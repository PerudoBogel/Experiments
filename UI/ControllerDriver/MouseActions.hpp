/*
 * MouseActions.hpp
 *
 *  Created on: 1 sie 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_MOUSEACTIONS_HPP_
#define UI_CONTROLLER_MOUSEACTIONS_HPP_

#include <windows.h>

class MouseActions{

public:
	MouseActions() :
			m_rightDown(false)
	{
	}

	bool isRigthClickDone(const MSG &m_message)
	{
		bool retVal = false;
		if (m_message.message == WM_RBUTTONDOWN)
			m_rightDown = true;

		if (m_message.message == WM_RBUTTONUP && m_rightDown)
		{
			m_rightDown = false;
			retVal = true;
		}

		return retVal;
	}

private:

	bool m_rightDown;

};

#endif /* UI_CONTROLLER_MOUSEACTIONS_HPP_ */
