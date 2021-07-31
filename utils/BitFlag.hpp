/*
 * bitFlag.hpp
 *
 *  Created on: 31 lip 2020
 *      Author: Jurek
 */

#ifndef UTILS_BITFLAG_HPP_
#define UTILS_BITFLAG_HPP_

class BitFlag{
public:
	template <typename bufferType, typename flagNo>
	inline static void setFlag(bufferType &flagContainer, flagNo flag)
	{
		flagContainer |= 1 << flag;
	}

	template <typename bufferType, typename flagNo>
	inline static void resetFlag(bufferType &flagContainer, flagNo flag)
	{
		flagContainer &= ~(1 << flag);
	}
private:
	BitFlag();
	~BitFlag();
};



#endif /* UTILS_BITFLAG_HPP_ */
