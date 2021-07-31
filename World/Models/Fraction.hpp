/*
 * Fraction.hpp
 *
 *  Created on: 31 lip 2020
 *      Author: Jurek
 */

#ifndef WORLD_MODELS_FRACTION_HPP_
#define WORLD_MODELS_FRACTION_HPP_

#include <BitFlag.hpp>

class Fraction
{
public:
	enum class Type
	{
		FRACTION_CATS,
		FRACTION_DOGS,
		FRACTION_HUMANS
	};

	Fraction() :
			m_fractionFlags(0)
	{
	}

	inline void addFraction(Type fraction)
	{
		BitFlag::setFlag(m_fractionFlags, static_cast<int>(fraction));
	}

	inline void removeFraction(Type fraction)
	{
		BitFlag::resetFlag(m_fractionFlags, static_cast<int>(fraction));
	}

	inline bool operator==(Fraction &fraction)
	{
		return fraction.m_fractionFlags & m_fractionFlags;
	}

private:
	unsigned long long int m_fractionFlags;
};

#endif /* WORLD_MODELS_FRACTION_HPP_ */
