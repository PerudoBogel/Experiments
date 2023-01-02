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

AIController::AIController(weak_ptr<Controller> pController) :
		m_pController(pController),
		m_nextPost(0)
{
}

void AIController::AddPost(Coordinates &&position)
{
	m_posts.push_back(position);
}

void AIController::Run()
{
	auto lockedController = m_pController.lock();
	if(!lockedController)
	{
		delete this;
		return;
	}
	
	auto lockedWorldEntity = lockedController->m_pEntity->getIWorld().lock();
	if (lockedWorldEntity)
	{
		Coordinates move;
		if (m_posts.empty())
		{
			move.x = Random::get(*lockedWorldEntity->m_pSpeed * 2) - *lockedWorldEntity->m_pSpeed;
			move.y = Random::get(*lockedWorldEntity->m_pSpeed * 2) - *lockedWorldEntity->m_pSpeed;
		}
		else
		{
			Coordinates post = m_posts[m_nextPost];
			Coordinates difference = post - *lockedWorldEntity->m_pPosition;
			Box postBox({100,100},post);
			if (difference.x > 0)
				move.x = *lockedWorldEntity->m_pSpeed > difference.x? *lockedWorldEntity->m_pSpeed : difference.x;
			if (difference.y > 0)
				move.y = *lockedWorldEntity->m_pSpeed > difference.y? *lockedWorldEntity->m_pSpeed : difference.y;
			if (difference.x < 0)
				move.x = *lockedWorldEntity->m_pSpeed < difference.x? *lockedWorldEntity->m_pSpeed : difference.x;
			if (difference.y < 0)
				move.y = *lockedWorldEntity->m_pSpeed < difference.y? *lockedWorldEntity->m_pSpeed : difference.y;
			if (postBox.Contains(*lockedWorldEntity->m_pPosition))
				m_nextPost++;
			if (m_nextPost >= m_posts.size())
				m_nextPost = 0;
		}

		lockedController->move(move);
	}
}

#endif /* UI_CONTROLLER_AICONTROLLER_C_ */
