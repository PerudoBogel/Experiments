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
		move.x = Random::get(3) - 1;
		move.y = Random::get(3) - 1;
	}
	else
	{
		Coordinates difference = m_posts[m_nextPost] - *m_controller.m_model->m_position;

		if (difference.x > 0)
			move.x++;
		if (difference.y > 0)
			move.y++;
		if (difference.x < 0)
			move.x--;
		if (difference.y < 0)
			move.y--;

		if (*m_controller.m_model->m_position == m_posts[m_nextPost])
			m_nextPost++;

		if (m_nextPost >= m_posts.size())
			m_nextPost = 0;
	}

	m_controller.move(move);
}

#endif /* UI_CONTROLLER_AICONTROLLER_C_ */
