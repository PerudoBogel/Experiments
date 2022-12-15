#pragma once
#include <math.h>

struct Coordinates
{
	float x, y, phi;

	Coordinates(): x(0), y(0), phi(0){}

	Coordinates(decltype(x) nx, decltype(y) ny, decltype(phi) nphi = 0): x(nx), y(ny),phi(nphi){}

	inline bool operator==(const Coordinates &coords)
	{
		return (x == coords.x) && (y == coords.y) && (phi == coords.phi);
	}

	inline Coordinates& operator+=(Coordinates &coords)
	{
		this->x += coords.x;
		this->y += coords.y;
		this->phi += coords.phi;
		return *this;
	}

	inline Coordinates& operator-=(Coordinates &coords)
	{
		this->x -= coords.x;
		this->y -= coords.y;
		this->phi -= coords.phi;
		return *this;
	}

	inline Coordinates& operator*=(float &value)
	{
		x *= value;
		y *= value;

		return *this;
	}

	inline bool operator!=(const Coordinates &coords)
	{
		return (x != coords.x) || (y != coords.y) || (phi != coords.phi);
	}

	inline Coordinates operator+(const Coordinates &pCoords)
	{
		auto tmpX = x + pCoords.x;
		auto tmpY = y + pCoords.y;
		auto tmpPhi = phi + pCoords.phi;

		return Coordinates(tmpX, tmpY, tmpPhi);
	}

	inline Coordinates operator-(const Coordinates &pCoords)
	{
		auto tmpX = x - pCoords.x;
		auto tmpY = y - pCoords.y;
		auto tmpPhi = phi - pCoords.phi;

		return Coordinates(tmpX, tmpY, tmpPhi);
	}

	inline Coordinates& operator=(const Coordinates &coords)
	{
		this->x = coords.x;
		this->y = coords.y;
		this->phi = coords.phi;
		return *this;
	}

	inline int distance(const Coordinates &coords)
	{
		return static_cast<int>(sqrt(pow(coords.x, 2) + pow(coords.y, 2)));
	}
};
