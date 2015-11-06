#pragma once

#include <algorithm>

#include "vertex.h"
#include "triangle.h"

template<typename T> class CBoundingBox
{
public:
	T x0, y0, x1, y1;
public:
	CBoundingBox<T>(const triangle<T>& triangle)
	{
		x0 = std::min(std::min(triangle.v0.v.x, triangle.v1.v.x), triangle.v2.v.x);
		y0 = std::min(std::min(triangle.v0.v.y, triangle.v1.v.y), triangle.v2.v.y);
		x1 = std::max(std::max(triangle.v0.v.x, triangle.v1.v.x), triangle.v2.v.x) + T(0.5);
		y1 = std::max(std::max(triangle.v0.v.y, triangle.v1.v.y), triangle.v2.v.y) + T(0.5);
	}
	CBoundingBox<T>(T _x0, T _y0, T _x1, T _y1) : x0(std::min(_x0, _x1)), y0(std::min(_y0, _y1)), x1(std::max(_x0, _x1) + T(0.5)), y1(std::max(_y0, _y1) + T(0.5)) {}
	~CBoundingBox() {}
};

typedef CBoundingBox<float> floatbb;
typedef CBoundingBox<double> doublebb;
