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

AIController::AIController(weak_ptr<World> pWorld, weak_ptr<IEntity> pEntity) :
		Controller(pWorld, pEntity),
		m_nextPost(0)
{
}

void AIController::AddPost(Coordinates &&position)
{
	m_posts.push_back(position);
}

void AIController::Run()
{	
	auto lockedMoveEntity = m_pEntity.lock()->getIMove().lock();
	if (lockedMoveEntity)
	{
		Coordinates moveStep;
		if (m_posts.empty())
		{
			moveStep.x = Random::get(*lockedMoveEntity->m_pSpeed * 2) - *lockedMoveEntity->m_pSpeed;
			moveStep.y = Random::get(*lockedMoveEntity->m_pSpeed * 2) - *lockedMoveEntity->m_pSpeed;
		}
		else
		{
			Coordinates post = m_posts[m_nextPost];
			Coordinates difference = post - *lockedMoveEntity->m_pPosition;
			Box postBox({100,100},post);
			if (difference.x > 0)
				moveStep.x = *lockedMoveEntity->m_pSpeed > difference.x? *lockedMoveEntity->m_pSpeed : difference.x;
			if (difference.y > 0)
				moveStep.y = *lockedMoveEntity->m_pSpeed > difference.y? *lockedMoveEntity->m_pSpeed : difference.y;
			if (difference.x < 0)
				moveStep.x = *lockedMoveEntity->m_pSpeed < difference.x? *lockedMoveEntity->m_pSpeed : difference.x;
			if (difference.y < 0)
				moveStep.y = *lockedMoveEntity->m_pSpeed < difference.y? *lockedMoveEntity->m_pSpeed : difference.y;
			if (postBox.Contains(*lockedMoveEntity->m_pPosition))
				m_nextPost++;
			if (m_nextPost >= m_posts.size())
				m_nextPost = 0;
		}

		Move(moveStep);
	}
	
    Controller::Run();
}

#endif /* UI_CONTROLLER_AICONTROLLER_C_ */
