#pragma once

struct Size
{
	int w, h;
	Size() :
			w(0), h(0)
	{
	}

	Size(int nw, int nh) :
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
};
