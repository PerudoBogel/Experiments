/*
 * ActionAttask.hpp
 *
 *  Created on: 31 maj 2020
 *      Author: Jurek
 */

#ifndef CONTROL_ACTIONS_ACTIONATTACK_HPP_
#define CONTROL_ACTIONS_ACTIONATTACK_HPP_

#include "World.hpp"
#include "Random.hpp"
#include "Box.hpp"
#include "IAttackEntity.hpp"
#include "Debug.hpp"

#include <vector>
#include <memory>
#include <array>

using namespace std;

namespace
{
	struct attackChance
	{
		int ratioX1000;
		int probabilityx1000;
	};

	template<int lookUpSize>
	struct AttackChanceLookUp
	{
		std::array<attackChance, lookUpSize> m_lookUp;
		
		const int ratioMin = 100, ratioMax = 10000;
		const int probabilityMin = 5, probabilityMax = 995;

		constexpr AttackChanceLookUp()
		{
			for (size_t index = 0; index < lookUpSize; index++)
			{
				m_lookUp[index].ratioX1000 = setRatio(index, lookUpSize);
				m_lookUp[index].probabilityx1000 = setProbability(index,
						lookUpSize);
			}
		}

		constexpr int setRatio(int index, int maxIndex)
		{
			float ratio = index / maxIndex;
			ratio *= ratioMax - ratioMin;
			ratio += ratioMin;

			return static_cast<int>(ratio);
		}

		constexpr int setProbability(int index, int maxIndex)
		{
			float probability = index / maxIndex;
			probability *= probabilityMax - probabilityMin;
			probability += probabilityMin;

			return static_cast<int>(probability);
		}

		int getAttackProbability(int ADRatio) const
		{
			int retVal;
			if (ADRatio < m_lookUp.begin()->ratioX1000)
			{
				retVal = m_lookUp.begin()->probabilityx1000;
			}else if (ADRatio > m_lookUp.end()->ratioX1000)
			{
				retVal = m_lookUp.end()->probabilityx1000;
			}else
			{
				for (auto element = m_lookUp.begin() + 1, previous = m_lookUp.begin();
						element != m_lookUp.end(); element++)
				{
					if (ADRatio < element->ratioX1000 && ADRatio >= previous->ratioX1000)
					{
						retVal = element->probabilityx1000;
						break;
					}
				}
			}

			return retVal;
		}
	};

	const AttackChanceLookUp<256> attackChanceLookUp;
}

class ActionAttack
{
public:
	enum Status
	{
		DONE, TARGET_TOO_FAR, MISSED, CANNOT_ATTACK
	};

	static int Execute(IAttackEntity& attacker, IAttackEntity &target)
	{
		int retVal = DONE;
		int ADRatio = 1000 * attacker.m_attack / target.m_defence;
		int Probability = attackChanceLookUp.getAttackProbability(ADRatio);
		
		if (attacker.m_position.distance(target.m_position) > attacker.m_range)
		{
			retVal = TARGET_TOO_FAR;
		}

		if(retVal != DONE)
		{
			//nothing just pass
		}
		else if (Random::get(1000) > Probability )
		{
			retVal = MISSED;
		}
		else if (attacker.m_allyFractions & target.m_memberFractions)
		{
			retVal = CANNOT_ATTACK;
		}
		
		if(retVal == DONE)
		{
			target.m_health -= attacker.m_damage;
			
			if(0 >= target.m_health)
			{
				target.m_isAlive = false;
			}
		}

		return retVal;
	}
private:
	ActionAttack() = delete;
};

#endif /* CONTROL_ACTIONS_ACTIONATTACK_HPP_ */
