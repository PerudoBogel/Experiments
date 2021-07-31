/*
 * AIController.h
 *
 *  Created on: 16 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_AICONTROLLER_HPP_
#define UI_CONTROLLER_AICONTROLLER_HPP_

#include <memory>
#include <vector>
#include "Coordinates.hpp"
#include "Controller.hpp"

class AIController {
public:
	AIController() = delete;
	AIController(Controller controller);

	void AddPost(Coordinates &&position);

	void Run();

    Controller m_controller;
private:

    size_t m_nextPost;
    std::vector<Coordinates> m_posts;
};

#endif /* UI_CONTROLLER_AICONTROLLER_HPP_ */
