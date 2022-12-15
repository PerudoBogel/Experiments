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
#include <iostream>

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
		int x_index = (int)coordinates.x / ISector::m_Size.w;
		int y_index = (int)coordinates.y / ISector::m_Size.h;
		int w_index = m_size.w / ISector::m_Size.w;
		int sectorIndex = x_index + y_index * w_index;

		if (coordinates.x >= m_size.w || coordinates.y >= m_size.h ||
			coordinates.x < 0 || coordinates.y < 0 ||
			sectorIndex > m_map.size())
			return nullptr;
		else
			return m_map[sectorIndex];
	}

	const Size m_size;
	const std::vector<ISector*> &m_map;
};

#endif /* WORLD_MAP_MAP_HPP_ */
