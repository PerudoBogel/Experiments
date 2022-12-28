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
			m_rightDown(false),
			m_leftDown(false)
	{
	}

	bool isRigthClickDone(const MSG &m_message)
	{
		bool retVal = false;
		if (m_message.message == WM_RBUTTONDOWN)
		{
			m_rightDown = true;
		}else if (m_message.message == WM_RBUTTONUP && m_rightDown)
		{
			m_rightDown = false;
			retVal = true;
		}

		return retVal;
	}
	
	bool isLeftClickDone(const MSG &m_message)
	{
		bool retVal = false;
		if (m_message.message == WM_LBUTTONDOWN)
		{
			m_leftDown = true;
		}else if (m_message.message == WM_LBUTTONUP && m_leftDown)
		{
			m_leftDown = false;
			retVal = true;
		}

		return retVal;
	}

private:

	bool m_rightDown;
	bool m_leftDown;

};

#endif /* UI_CONTROLLER_MOUSEACTIONS_HPP_ */
