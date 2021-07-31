/*
 * ActionAttask.hpp
 *
 *  Created on: 31 maj 2020
 *      Author: Jurek
 */

#ifndef CONTROL_ACTIONS_ACTIONATTACK_HPP_
#define CONTROL_ACTIONS_ACTIONATTACK_HPP_

#include "World.hpp"
#include "IModel.hpp"
#include "Random.hpp"
#include "ReactionAttack.hpp"
#include <vector>
#include <memory>
#include <array>
#include "Box.hpp"

namespace
{

int ratioMin = 100, ratioMax = 10000;
int probabilityMin = 5, probabilityMax = 995;

struct attackChance
{
	int ratioX1000;
	int probabilityx1000;
};

template<int lookUpSize>
struct AttackChanceLookUp
{
	std::array<attackChance, lookUpSize> m_lookUp;

	constexpr AttackChanceLookUp()
	{
		for (size_t index = 0; index < m_lookUp.size(); index++)
		{
			m_lookUp[index].ratioX1000 = setRatio(index, lookUpSize);
			m_lookUp[index].probabilityx1000 = setProbability(index,
					lookUpSize);
		}
	}

	constexpr int setRatio(int Index, int maxIndex)
	{
		int stepSize = (ratioMax - ratioMin) / maxIndex;

		return ratioMin + stepSize * Index;
	}

	constexpr int setProbability(int Index, int maxIndex)
	{
		int stepSize = (probabilityMax - probabilityMin) / maxIndex;

		return probabilityMin + stepSize * Index;
	}
};

const AttackChanceLookUp<128> attackChanceLookUp;

int interpolateAttackProbability(const attackChance &point1,
		const attackChance &point2, int ratio)
{
	int diffRatio = ratio - point1.ratioX1000;
	int ratioRange = point2.ratioX1000 - point1.ratioX1000;
	int ProbabilityRange = point2.probabilityx1000 - point1.probabilityx1000;
	return diffRatio * ProbabilityRange / ratioRange;
}

int getAttackProbability(int ADRatio)
{
	int retVal;
	if (ADRatio < attackChanceLookUp.m_lookUp.begin()->ratioX1000)
		retVal = attackChanceLookUp.m_lookUp.begin()->probabilityx1000;
	else if (ADRatio > (attackChanceLookUp.m_lookUp.end())->ratioX1000)
		retVal = (attackChanceLookUp.m_lookUp.end())->ratioX1000;
	else
		for (auto element = attackChanceLookUp.m_lookUp.begin();
				element != attackChanceLookUp.m_lookUp.end(); element++)
			if (ADRatio < element->ratioX1000)
			{
				auto currentElement = element;
				retVal = interpolateAttackProbability(*(--element),
						*currentElement, ADRatio);
				break;
			}

	return retVal;
}
}

class ActionAttack
{
public:
	enum
	{
		DONE, TARGET_TOO_FAR, MISSED, CANNOT_ATTACK, NO_TARGET
	};

	static int Execute(std::shared_ptr<World> pWorld,
			std::shared_ptr<IModel> attacker, Coordinates &target)
	{
		int retVal = NO_TARGET;
		bool targetFound = false;
		std::shared_ptr<IModel> pTargetModel;

		for (auto pModel : *pWorld->getModels().get())
		{
			if (Box(pModel->getSize(), pModel->getPosition()).Contains(target))
			{
				targetFound = true;
				pTargetModel = pModel;
				break;
			}
		}

		if (attacker.get() == pTargetModel.get())
			targetFound = false;

		if (targetFound)
		{
			int ADRatio = 1000 * attacker->m_attack / pTargetModel->m_defence;
			int Probability = getAttackProbability(ADRatio);

			if (attacker->getPosition().distance(pTargetModel->getPosition())
					> attacker->m_range)
			{
				retVal = TARGET_TOO_FAR;
			}
			else if (Random::get(1000) < Probability)
			{
				switch (ReactionAttack::Execute(attacker, pTargetModel))
				{
				case ReactionAttack::DONE:
					retVal = DONE;
					break;
				case ReactionAttack::CANNOT_ATTACK:
					retVal = CANNOT_ATTACK;
					break;
				default:
					retVal = MISSED;
					break;
				}
			}
			else
			{
				retVal = MISSED;
			}
		}

		return retVal;
	}
private:
	ActionAttack() = delete;
};

#endif /* CONTROL_ACTIONS_ACTIONATTACK_HPP_ */
