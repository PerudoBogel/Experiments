/*
 * AIController.c
 *
 *  Created on: 16 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_AICONTROLLER_C_
#define UI_CONTROLLER_AICONTROLLER_C_

#include <array>
#include "AIController.hpp"
#include "Random.hpp"

AIController::AIController(Controller controller) :
		m_controller(controller),m_nextPost(0)
{
}

void AIController::AddPost(Coordinates &&position)
{
	m_posts.push_back(position);
}

void AIController::Run()
{
	Coordinates move;
	if (m_posts.empty())
	{
		move.x = Random::get(m_controller.m_model->m_speed * 2) - m_controller.m_model->m_speed;
		move.y = Random::get(m_controller.m_model->m_speed * 2) - m_controller.m_model->m_speed;
	}
	else
	{
		Coordinates post = m_posts[m_nextPost];
		Coordinates difference = post - m_controller.m_model->m_position;
		Box postBox({100,100},post);

		if (difference.x > 0)
			move.x = m_controller.m_model->m_speed > difference.x? m_controller.m_model->m_speed : difference.x;
		if (difference.y > 0)
			move.y = m_controller.m_model->m_speed > difference.y? m_controller.m_model->m_speed : difference.y;
		if (difference.x < 0)
			move.x = m_controller.m_model->m_speed < difference.x? m_controller.m_model->m_speed : difference.x;
		if (difference.y < 0)
			move.y = m_controller.m_model->m_speed < difference.y? m_controller.m_model->m_speed : difference.y;

		if (postBox.Contains(m_controller.m_model->m_position))
			m_nextPost++;

		if (m_nextPost >= m_posts.size())
			m_nextPost = 0;
	}

	m_controller.move(move);
}

#endif /* UI_CONTROLLER_AICONTROLLER_C_ */
