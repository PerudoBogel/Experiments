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

class AIController: public Controller
{
public:
	AIController() = delete;
	AIController(weak_ptr<World> pWorld, shared_ptr<IEntity> pEntity);

	void AddPost(Coordinates &&position);

	void Run();
	ControllerType GetType(){return CONTROL_AI;}
private:

    size_t m_nextPost;
    std::vector<Coordinates> m_posts;
};

#endif /* UI_CONTROLLER_AICONTROLLER_HPP_ */
