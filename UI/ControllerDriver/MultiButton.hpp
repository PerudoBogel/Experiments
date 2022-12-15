/*
 * multiButton.hpp
 *
 *  Created on: 17 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_MULTIBUTTON_HPP_
#define UI_CONTROLLER_MULTIBUTTON_HPP_

#include <array>
#include <windows.h>

#define NUMBER_OF_BUTTONS 64

class MultiButton
{
public:

	MultiButton() :
			m_button(
			{ })
	{
	}

	void registerMsg(const MSG &m_message)
	{
		if (m_message.message == WM_KEYDOWN)
		{
			bool alreadyPresent = false;
			for (auto button : m_button)
				if (button == m_message.wParam)
					alreadyPresent = true;
			if (!alreadyPresent)
				for (auto button = m_button.begin(); button != m_button.end();
						++button)
					if (*button == 0)
					{
						*button = m_message.wParam;
						break;
					}
		}
		else if (m_message.message == WM_KEYUP)
			for (auto button = m_button.begin(); button != m_button.end();
					++button)
				if (*button == m_message.wParam)
					*button = 0;
	}

	const std::array<WPARAM, NUMBER_OF_BUTTONS>& get() const
	{
		return m_button;
	}

private:
	std::array<WPARAM, NUMBER_OF_BUTTONS> m_button;
};

#endif /* UI_CONTROLLER_MULTIBUTTON_HPP_ */
