/*
 * bitMap.hpp
 *
 *  Created on: 31 lip 2020
 *      Author: Jurek
 */

#ifndef UTILS_BITMAP_HPP_
#define UTILS_BITMAP_HPP_

template <typename bufferType, typename flagType>
class BitMask{
public:
	BitMask(){}
	BitMask(const BitMask &bitMask):m_mask(bitMask.m_mask){}


	inline void set(const flagType flag)
	{
		m_mask |= 1 << static_cast<int>(flag);
	}

	inline void clear(const flagType flag)
	{
		m_mask &= ~(1 << static_cast<int>(flag));
	}

	inline BitMask operator+(const BitMask &bitMask) const
	{
		return BitMask(m_mask | bitMask.m_mask);
	}
	
	inline BitMask operator-(const BitMask &bitMask) const
	{
		return BitMask(m_mask & (!bitMask.m_mask));
	}
	
	inline bool operator==(const BitMask &bitMask) const
	{
		return (m_mask == bitMask.m_mask);
	}

	inline bool operator!=(const BitMask &bitMask) const
	{
		return (m_mask != bitMask.m_mask);
	}

private:
	BitMask(const bufferType &mask):m_mask(mask){}
	bufferType m_mask;
};



#endif /* UTILS_BITMAP_HPP_ */
