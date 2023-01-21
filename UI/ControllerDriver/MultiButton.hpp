/*
 * multiButton.hpp
 *
 *  Created on: 17 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_MULTIBUTTON_HPP_
#define UI_CONTROLLER_MULTIBUTTON_HPP_

#include <array>
#include "SFML/Window.hpp"

class MultiButton
{
public:

	MultiButton():
	m_button({})
	{
	}

	void updateEvent(const sf::Event &event)
	{
		if(event.key.code == sf::Keyboard::Key::Unknown)
		{}
		if (event.type == sf::Event::KeyPressed)
			m_button[event.key.code] = true;
		else if (event.type == sf::Event::KeyReleased)
			m_button[event.key.code] = false;
	}

	const std::array<bool, sf::Keyboard::Key::KeyCount>& get() const
	{
		return m_button;
	}

	int getPressedCount()
	{
		int pressedKeyCount = 0;
		for(auto button : m_button)
			if(button)
				pressedKeyCount++;
		
		return pressedKeyCount;
	}


private:
	std::array<bool, sf::Keyboard::Key::KeyCount> m_button;
};

#endif /* UI_CONTROLLER_MULTIBUTTON_HPP_ */
