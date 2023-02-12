/*
 * AIController.c
 *
 *  Created on: 16 maj 2020
 *      Author: Jurek
 */

#ifndef UI_CONTROLLER_AICONTROLLER_C_
#define UI_CONTROLLER_AICONTROLLER_C_

#include "AIController.hpp"
#include "Random.hpp"

#include <array>
#include <assert.h>

AIController::AIController(weak_ptr<World> pWorld, shared_ptr<IEntity> pEntity):
		Controller(pWorld, pEntity),
		m_nextPost(0)
{}

void AIController::AddPost(Coordinates &&position)
{
	m_posts.push_back(position);
}

void AIController::Run()
{	
    Controller::Run();

	IMoveEntity moveEntity;
	if (m_pEntity->getIMove(moveEntity))
	{
		Coordinates moveStep;
		if (m_posts.empty())
		{
			moveStep.x = Random::get(moveEntity.m_speed * 2) - moveEntity.m_speed;
			moveStep.y = Random::get(moveEntity.m_speed * 2) - moveEntity.m_speed;
		}
		else
		{
			Coordinates post = m_posts[m_nextPost];
			Coordinates difference = post - moveEntity.m_position;
			Box postBox({100,100},post);
			if (difference.x > 0)
				moveStep.x = moveEntity.m_speed > difference.x? moveEntity.m_speed : difference.x;
			if (difference.y > 0)
				moveStep.y = moveEntity.m_speed > difference.y? moveEntity.m_speed : difference.y;
			if (difference.x < 0)
				moveStep.x = moveEntity.m_speed < difference.x? moveEntity.m_speed : difference.x;
			if (difference.y < 0)
				moveStep.y = moveEntity.m_speed < difference.y? moveEntity.m_speed : difference.y;
			if (postBox.Contains(moveEntity.m_position))
				m_nextPost++;
			if (m_nextPost >= m_posts.size())
				m_nextPost = 0;
		}

		Move(moveStep);
	}
}

#endif /* UI_CONTROLLER_AICONTROLLER_C_ */
