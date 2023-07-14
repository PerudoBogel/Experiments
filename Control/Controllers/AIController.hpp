/*
 * AIController.h
 *
 *  Created on: 16 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_AICONTROLLER_HPP_
#define UI_CONTROLLER_AICONTROLLER_HPP_

#include "Coordinates.hpp"
#include "ControllerBase.hpp"

#include <memory>
#include <vector>

using namespace std;

class AIController: public ControllerBase
{
public:
	AIController() = delete;
	AIController(weak_ptr<World> pWorld, shared_ptr<Entity> pEntity);

	void AddPost(Coordinates &&position);

	void Run();
	ControllerType GetType(){return CONTROL_AI;}
private:

    size_t m_nextPost;
    std::vector<Coordinates> m_posts;
};

#endif /* UI_CONTROLLER_AICONTROLLER_HPP_ */
