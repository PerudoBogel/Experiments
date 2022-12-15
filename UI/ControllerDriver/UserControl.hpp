/*
 * UserControl.hpp
 *
 *  Created on: 23 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_USERCONTROL_HPP_
#define UI_CONTROLLER_USERCONTROL_HPP_

#include <windows.h>
#include <memory>
#include "Coordinates.hpp"
#include "IModel.hpp"
#include "MultiButton.hpp"
#include "MouseActions.hpp"
#include "Controller.hpp"

class UserControl{
public:
	enum{
		DONE,
		QUIT
	};
	UserControl(Controller&& pController);
	int run();
private:
	struct Move
	{
		WPARAM m_symbol;
		Coordinates move;
	};
	char m_input;
	static Move m_moves[];

    MSG m_message;
    MultiButton m_multibutton;
    MouseActions m_mouseActions;


	Controller m_controller;
};



#endif /* UI_CONTROLLER_USERCONTROL_HPP_ */
