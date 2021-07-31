/*
 * ReactionDeffend.hpp
 *
 *  Created on: 31 maj 2020
 *      Author: Jurek
 */

#ifndef CONTROL_REACTIONS_REACTIONATTACK_HPP_
#define CONTROL_REACTIONS_REACTIONATTACK_HPP_

#include "IModel.hpp"
#include <memory>

class ReactionAttack{
public:
	enum
	{
		DONE, CANNOT_ATTACK
	};

	static int Execute(std::shared_ptr<IModel> attacker,
			std::shared_ptr<IModel> target)
	{
		int retVal;

		if (attacker->m_allyFractions == target->m_memberFractions)
		{
			retVal = CANNOT_ATTACK;
		}
		else
		{
			target->m_health -= attacker->m_damage;
			retVal = DONE;
		}
		return retVal;
	}
private:
	ReactionAttack() = delete;
};


#endif /* CONTROL_REACTIONS_REACTIONATTACK_HPP_ */
