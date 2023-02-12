#pragma once
#include "Coordinates.hpp"
#include "Size.hpp"

struct Box
{
	Box(void){}
	Box(const Size &size, const Coordinates &position)
	{
		calculate(size, position);
	}
	
	float Xmin, Xmax;
	float Ymin, Ymax;
	
    Box& operator=( const Box& ) = default;

	inline void calculate(const Size &size, const Coordinates &position)
	{
		Xmin = position.x - size.w / 2; 
		Xmax = position.x + size.w / 2; 
		Ymin = position.y - size.h / 2;
		Ymax = position.y + size.h / 2;
	}

	inline bool isCollision(const Box &box) const
	{
		bool noCollision = false;

		noCollision |= this->Xmin > box.Xmax;
		noCollision |= this->Ymin > box.Ymax;

		noCollision |= this->Xmax < box.Xmin;
		noCollision |= this->Ymax < box.Ymin;

		return !noCollision;
	}

	static inline Coordinates ColissionDir(const Box &moving ,const Box &target)
	{
		Coordinates out;

		if (moving.Ymin > target.Ymax)
			out.y--;
		if (target.Ymin > moving.Ymax)
			out.y++;
		if (moving.Xmin > target.Xmax)
			out.x--;
		if (target.Xmin > moving.Xmax)
			out.x++;

		return out;
	}

	inline bool Contains(const Coordinates &coordinates)
	{
		bool retVal = true;

		retVal &= coordinates.y >= Ymin;
		retVal &= coordinates.y <= Ymax;
		retVal &= coordinates.x >= Xmin;
		retVal &= coordinates.x <= Xmax;

		return retVal;
	}
};
