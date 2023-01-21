/*
 * MouseActions.hpp
 *
 *  Created on: 1 sie 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_MOUSEACTIONS_HPP_
#define UI_CONTROLLER_MOUSEACTIONS_HPP_

#include "Debug.hpp"
#include "SFML/Window.hpp"

class MouseActions{

public:

	enum {
		STATE_NONE,
		STATE_R_PRESSED,
		STATE_R_DOWN,
		STATE_R_RELEASED,
		STATE_R_UP,
		STATE_L_PRESSED,
		STATE_L_DOWN,
		STATE_L_RELEASED,
		STATE_L_UP
	};

	MouseActions() :
			m_rightState(STATE_NONE),
			m_leftState(STATE_NONE)
	{
	}

	void updateEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Button::Left)
				m_leftState = STATE_L_PRESSED;
			else if (event.mouseButton.button == sf::Mouse::Button::Right)
				m_rightState = STATE_R_PRESSED;
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			if(event.mouseButton.button == sf::Mouse::Button::Left)
				m_leftState = STATE_L_RELEASED;
			else if (event.mouseButton.button == sf::Mouse::Button::Right)
				m_rightState = STATE_R_RELEASED;
		}
		else if(event.type == sf::Event::MouseMoved)
		{
			m_x = event.mouseMove.x;
			m_y = event.mouseMove.y;
		}
	}

	void Run()
	{
		if(m_rightState == STATE_R_PRESSED)
			m_rightState = STATE_R_DOWN;
		else if(m_rightState == STATE_R_RELEASED)
			m_rightState = STATE_R_UP;

		if(m_leftState == STATE_L_PRESSED)
			m_leftState = STATE_L_DOWN;
		else if(m_leftState == STATE_L_RELEASED)
			m_leftState = STATE_L_UP;
	}

	int m_rightState;
	int m_leftState;
	int m_x,m_y;
};

#endif /* UI_CONTROLLER_MOUSEACTIONS_HPP_ */
