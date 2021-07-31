/*
 * Map.hpp
 *
 *  Created on: 22 maj 2020
 *      Author: Jurek
 */

#ifndef WORLD_MAP_MAP_HPP_
#define WORLD_MAP_MAP_HPP_

#include "Size.hpp"
#include "Box.hpp"
#include "ISector.hpp"
#include <vector>

class Map
{
public:
	Map(Size size, const std::vector<ISector*> &pMap) :
			m_size(size.w * ISector::m_Size.w,
					size.h * ISector::m_Size.h),
			m_map(pMap)
	{
	}

	std::vector<ISector*> getBox(Box mapBox)
	{
	    std::vector<ISector*> outBuffer;

	    for (int yTmp = mapBox.Ymin; yTmp <= mapBox.Ymax; yTmp+=ISector::m_Size.h)
	        for (int xTmp = mapBox.Xmin; xTmp <= mapBox.Xmax; xTmp+=ISector::m_Size.w)
	            outBuffer.push_back(getSector(Coordinates(xTmp, yTmp)));

	    return outBuffer;
	}

	ISector* getSector(Coordinates coordinates)
	{
		Coordinates recalculated(coordinates.x/ ISector::m_Size.w, coordinates.y / ISector::m_Size.h);
		if (coordinates.x >= m_size.w || coordinates.y >= m_size.h || coordinates.x < 0 || coordinates.y < 0)
			return nullptr;
		else
	        return m_map[recalculated.x  + (m_size.w / ISector::m_Size.w  * recalculated.y)];
	}

	const Size m_size;
	const std::vector<ISector*> &m_map;
};

#endif /* WORLD_MAP_MAP_HPP_ */
