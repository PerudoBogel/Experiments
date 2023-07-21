#pragma once
#include <ostream>

struct Size
{
	float w, h;
	Size() :
			w(0), h(0)
	{
	}

	Size(decltype(w) nw, decltype(h) nh) :
			w(nw), h(nh)
	{
	}

	inline bool operator==(Size &size)
	{
		return (w == size.w) && (h == size.h);
	}

	inline Size operator=(const Size &size)
	{
		this->w = size.w;
		this->h = size.h;
		return *this;
	}

	inline Size operator+(const Size &pSize)
	{
		return Size(pSize.w + w, pSize.h + h);
	}

	inline Size operator-(const Size &pSize)
	{
		return Size(w - pSize.w, h - pSize.h);
	}

	friend std::ostream& operator<< (std::ostream& stream, Size &size)
	{
		stream << "( " << size.w << ", " << size.h << " )";
		return stream;
	}
};