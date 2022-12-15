/*
 * Fraction.hpp
 *
 *  Created on: 31 lip 2020
 *      Author: Jurek
 */

#ifndef WORLD_MODELS_FRACTION_HPP_
#define WORLD_MODELS_FRACTION_HPP_

#include <BitMask.hpp>

class Fraction
{
public:
	enum class Type
	{
		FRACTION_CATS,
		FRACTION_DOGS,
		FRACTION_HUMANS
	};

	Fraction(){}
	Fraction(const Fraction &fraction):m_fractionFlags(fraction.m_fractionFlags){}

	inline void addFraction(Type fractionType)
	{
		m_fractionFlags.set(fractionType);
	}

	inline void removeFraction(Type fractionType)
	{
		m_fractionFlags.clear(fractionType);
	}

	inline bool operator==(Fraction &fraction)
	{
		return m_fractionFlags == fraction.m_fractionFlags;
	}
	
	inline bool operator!=(Fraction &fraction)
	{
		return m_fractionFlags != fraction.m_fractionFlags;
	}
		
	inline Fraction operator+(Fraction &fraction)
	{
		return Fraction(m_fractionFlags + fraction.m_fractionFlags);
	}

	inline Fraction operator-(Fraction &fraction)
	{
		return Fraction(m_fractionFlags - fraction.m_fractionFlags);
	}

private:

	Fraction(const BitMask<uint64_t,Type> &fractionMap):m_fractionFlags(fractionMap){}
	BitMask<uint64_t,Type> m_fractionFlags;

};

#endif /* WORLD_MODELS_FRACTION_HPP_ */
