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

	inline Coordinates& operator+=(const Coordinates &coords)
	{
		x += coords.x;
		y += coords.y;
		phi += coords.phi;
		return *this;
	}

	inline Coordinates& operator-=(const Coordinates &coords)
	{
		x -= coords.x;
		y -= coords.y;
		phi -= coords.phi;
		return *this;
	}

	inline Coordinates& operator*=(const float &value)
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
		x = coords.x;
		y = coords.y;
		phi = coords.phi;
		return *this;
	}

	inline float distance(const Coordinates &coords)
	{
		return sqrt(pow(x - coords.x, 2) + pow(y - coords.y, 2));
	}
};
