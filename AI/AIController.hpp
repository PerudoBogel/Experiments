/*
 * AIController.h
 *
 *  Created on: 16 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_AICONTROLLER_HPP_
#define UI_CONTROLLER_AICONTROLLER_HPP_

#include "Coordinates.hpp"
#include "Controller.hpp"

#include <memory>
#include <vector>

using namespace std;

class AIController {
public:
	AIController() = delete;
	AIController(weak_ptr<Controller> pController);

	void AddPost(Coordinates &&position);

	void Run();

    weak_ptr<Controller> m_pController;
private:

    size_t m_nextPost;
    std::vector<Coordinates> m_posts;
};

#endif /* UI_CONTROLLER_AICONTROLLER_HPP_ */
