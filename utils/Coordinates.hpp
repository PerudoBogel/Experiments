#pragma once
#include <math.h>

struct Coordinates
{
	float x, y;

	Coordinates() :
			x(0), y(0)
	{
	}

	Coordinates(decltype(x) nx, decltype(x) ny) :
			x(nx), y(ny)
	{
	}

	inline bool operator==(const Coordinates &coords)
	{
		return (x == coords.x) && (y == coords.y);
	}

	inline Coordinates& operator+=(Coordinates &coords)
	{
		this->x += coords.x;
		this->y += coords.y;
		return *this;
	}

	inline Coordinates& operator-=(Coordinates &coords)
	{
		this->x -= coords.x;
		this->y -= coords.y;
		return *this;
	}

	inline Coordinates& operator*=(float &value)
	{
		int tmpx = static_cast<int>(this->x * value);
		int tmpy = static_cast<int>(this->y * value);

		if (tmpx == 0)
		{
			if (this->x > 0)
				this->x = 1;
			else if (this->x < 0)
				this->x = -1;
		}
		else
			this->x = tmpx;

		if (tmpy == 0)
		{
			if (this->y > 0)
				this->y = 1;
			else if (this->y < 0)
				this->y = -1;
		}
		else
			this->y = tmpy;

		return *this;
	}

	inline bool operator!=(const Coordinates &coords)
	{
		return (x != coords.x) || (y != coords.y);
	}

	friend Coordinates operator+(Coordinates lCoords, const Coordinates &pCoords)
	{
		lCoords.x += pCoords.x;
		lCoords.y += pCoords.y;

		return lCoords;
	}

	friend Coordinates operator-(Coordinates lCoords, const Coordinates &pCoords)
	{
		lCoords.x -= pCoords.x;
		lCoords.y -= pCoords.y;

		return lCoords;
	}

	inline Coordinates& operator=(const Coordinates &coords)
	{
		this->x = coords.x;
		this->y = coords.y;
		return *this;
	}

	inline int distance(const Coordinates &coords)
	{
		return static_cast<int>(sqrt(pow(coords.x, 2) + pow(coords.y, 2)));
	}
};
