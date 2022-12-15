#pragma once

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

	inline Size& operator=(const Size &size)
	{
		this->w = size.w;
		this->h = size.h;
		return *this;
	}

	friend Size operator+(Size lSize, const Size &pSize)
	{
		lSize.w += pSize.w;
		lSize.h += pSize.h;

		return lSize;
	}
};
