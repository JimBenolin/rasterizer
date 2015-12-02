#pragma once

#include "vector2.h"
#include "vector3.h"


template<typename T> class boundingbox1d
{
public:
	T min, max;
public:
	boundingbox1d<T>(void)
	{
		min = max = T(0);
	}
	boundingbox1d<T>(T _x0, T _x1)
	{
		min = std::min(_x0, _x1);
		max = std::max(_x0, _x1);
	}
	~boundingbox1d<T>() {}

	inline T left(void) const { return min; }
	inline T right(void) const { return max; }

	bool operator==(const boundingbox1d<T>& box) { return (min == box.min && max == box.max); }
	bool operator!=(const boundingbox1d<T>& box) { return !(*this == box); }
	boundingbox1d<T> operator+(const boundingbox1d<T>& box) const { return boundingbox1d<T>(std::min(min, box.min), std::max(max, box.max)); }
	boundingbox1d<T> operator/(const boundingbox1d<T>& box) const { if (!this->overlaps(box)) return boundingbox1d<T>(T(0), T(0)); return boundingbox1d<T>(std::max(min, box.min), std::min(max, box.max)); }
	boundingbox1d<T>& operator+=(const boundingbox1d<T>& box) { return *this = *this + box; }
	boundingbox1d<T>& operator/=(const boundingbox1d<T>& box) { return *this = *this / box; }

	inline bool empty(void) const { return min == max; }

	inline void clamp(const T xMin, const T xMax)
	{
		min = jmath::clamp<T>(min, xMin, xMax);
		max = jmath::clamp<T>(max, xMin, xMax);
	}

	inline void offset(const T offset)
	{
		min += offset;
		max += offset;
	}

	bool overlaps(const boundingbox1d<T>& box) const
	{
		if (min >= box.max)
			return false;
		if (max <= box.min)
			return false;
		return true;
	}

	bool inside(const boundingbox1d<T>& box) const
	{
		if (min < box.min)
			return false;
		if (max > box.max)
			return false;
		return true;
	}
};

typedef boundingbox1d<int> intbb1d;
typedef boundingbox1d<unsigned int> uintbb1d;
typedef boundingbox1d<float> floatbb1d;
typedef boundingbox1d<double> doublebb1d;

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> class boundingbox2d
{
public:
	vector2<T> min, max;
public:
	boundingbox2d<T>(void)
	{
		min = max = vector2<T>(T(0), T(0));
	}
	boundingbox2d<T>(T x0, T y0, T x1, T y1)
	{
		min.x = std::min(x0, x1);
		max.x = std::max(x0, x1);
		min.y = std::min(y0, y1);
		max.y = std::max(y0, y1);
	}
	boundingbox2d<T>(const vector2<T>& v0, const vector2<T>& v1)
	{
		min.x = std::min(v0.x, v1.x);
		max.x = std::max(v0.x, v1.x);
		min.y = std::min(v0.y, v1.y);
		max.y = std::max(v0.y, v1.y);
	}
	boundingbox2d<T>(const vector2<T>& v0, const vector2<T>& v1, const vector2<T>& v2)
	{
		min.x = std::min(std::min(v0.x, v1.x), v2.x);
		max.x = std::max(std::max(v0.x, v1.x), v2.x);
		min.y = std::min(std::min(v0.y, v1.y), v2.y);
		max.y = std::max(std::max(v0.y, v1.y), v2.y);
	}
	~boundingbox2d<T>() {}

	inline T left(void) const { return min.x; }
	inline T right(void) const { return max.x; }
	inline T top(void) const { return max.y; }
	inline T bottom(void) const { return min.y; }

	bool operator==(const boundingbox2d<T>& box) const { return (min.x == box.min.x && max.x == box.max.x && min.y == box.min.y && max.y == box.max.y); }
	bool operator!=(const boundingbox2d<T>& box) const { return !(*this == box); }
	boundingbox2d<T> operator+(const boundingbox2d<T>& box) const { return boundingbox2d<T>(std::min(min.x, box.min.x), std::min(min.y, box.min.y), std::max(max.x, box.max.x), std::max(max.y, box.max.y)); }
	boundingbox2d<T> operator/(const boundingbox2d<T>& box) const { if (!this->overlaps(box)) return boundingbox2d<T>(T(0), T(0), T(0), T(0)); return boundingbox2d<T>(std::max(min.x, box.min.x), std::max(min.y, box.min.y), std::min(max.x, box.max.x), std::min(max.y, box.max.y)); }
	boundingbox2d<T>& operator+=(const boundingbox2d<T>& box) { return *this = *this + box; }
	boundingbox2d<T>& operator/=(const boundingbox2d<T>& box) { return *this = *this / box; }

	inline bool empty(void) const { return min.x == max.x || min.y == max.y; }

	inline void clamp(const T xMin, const T yMin, const T xMax, const T yMax)
	{
		min.x = jmath::clamp<T>(min.x, xMin, xMax);
		max.x = jmath::clamp<T>(max.x, xMin, xMax);
		min.y = jmath::clamp<T>(min.y, yMin, yMax);
		max.y = jmath::clamp<T>(max.y, yMin, yMax);
	}

	inline void offset(const T xOffset, const T yOffset)
	{
		min.x += xOffset;
		max.x += xOffset;
		min.y += yOffset;
		max.y += yOffset;
	}

	bool overlaps(const boundingbox2d<T>& box) const
	{
		if (min.x >= box.max.x)
			return false;
		if (max.x <= box.min.x)
			return false;
		if (min.y >= box.max.y)
			return false;
		if (max.y <= box.min.y)
			return false;
		return true;
	}

	bool inside(const boundingbox2d<T>& box) const
	{
		if (min.x < box.min.x)
			return false;
		if (max.x > box.max.x)
			return false;
		if (min.y < box.min.y)
			return false;
		if (max.y > box.max.y)
			return false;
		return true;
	}
};

typedef boundingbox2d<int> intbb2d;
typedef boundingbox2d<unsigned int> uintbb2d;
typedef boundingbox2d<float> floatbb2d;
typedef boundingbox2d<double> doublebb2d;

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> class boundingbox3d
{
public:
	vector3<T> min, max;
public:
	boundingbox3d<T>(T x0, T y0, T z0, T x1, T y1, T z1)
	{
		min.x = std::min(x0, x1);
		max.x = std::max(x0, x1);
		min.y = std::min(y0, y1);
		max.y = std::max(y0, y1);
		min.z = std::min(z0, z1);
		max.z = std::max(z0, z1);
	}
	boundingbox3d<T>(const vector3<T>& v0, const vector3<T>& v1)
	{
		min.x = std::min(v0.x, v1.x);
		max.x = std::max(v0.x, v1.x);
		min.y = std::min(v0.y, v1.y);
		max.y = std::max(v0.y, v1.y);
		min.z = std::min(v0.z, v1.z);
		max.z = std::max(v0.z, v1.z);
	}
	~boundingbox3d<T>() {}

	inline T left(void) const { return min.x; }
	inline T right(void) const { return max.x; }
	inline T top(void) const { return max.y; }
	inline T bottom(void) const { return min.y; }
	inline T near(void) const { return max.z; }
	inline T far(void) const { return min.z; }

	bool operator==(const boundingbox3d<T>& box) const { return (min.x == box.min.x && max.x == box.max.x && min.y == box.min.y && max.y == box.max.y && min.z == box.min.z && max.z == box.max.z); }
	bool operator!=(const boundingbox3d<T>& box) const { return !(*this == box); }
	boundingbox3d<T> operator+(const boundingbox3d<T>& box) const { return boundingbox3d<T>(std::min(min.x, box.min.x), std::min(min.y, box.min.y), std::min(min.z, box.min.z), std::max(max.x, box.max.x), std::max(max.y, box.max.y), std::max(max.z, box.max.z)); }
	boundingbox3d<T> operator/(const boundingbox3d<T>& box) const { if (!this->overlaps(box)) return boundingbox3d<T>(T(0), T(0), T(0), T(0), T(0), T(0)); return boundingbox3d<T>(std::max(min.x, box.min.x), std::max(min.y, box.min.y), std::max(min.z, box.min.z), std::min(max.x, box.max.x), std::min(max.y, box.max.y), std::min(max.z, box.max.z)); }
	boundingbox3d<T>& operator+=(const boundingbox3d<T>& box) { return *this = *this + box; }
	boundingbox3d<T>& operator/=(const boundingbox3d<T>& box) { return *this = *this / box; }

	inline bool empty(void) const { return min.x == max.x || min.y == max.y || min.z == max.z; }

	inline void clamp(const T xMin, const T yMin, const T zMin, const T xMax, const T yMax, const T zMax)
	{
		min.x = jmath::clamp<T>(min.x, xMin, xMax);
		max.x = jmath::clamp<T>(max.x, xMin, xMax);
		min.y = jmath::clamp<T>(min.y, yMin, yMax);
		max.y = jmath::clamp<T>(max.y, yMin, yMax);
		min.z = jmath::clamp<T>(min.y, zMin, zMax);
		max.z = jmath::clamp<T>(max.y, zMin, zMax);
	}

	inline void offset(const T xOffset, const T yOffset, const T zOffset)
	{
		min.x += xOffset;
		max.x += xOffset;
		min.y += yOffset;
		max.y += yOffset;
		min.z += zOffset;
		max.z += zOffset;
	}

	bool overlaps(const boundingbox3d<T>& box) const
	{
		if (min.x >= box.max.x)
			return false;
		if (max.x <= box.min.x)
			return false;
		if (min.y >= box.max.y)
			return false;
		if (max.y <= box.min.y)
			return false;
		if (min.z >= box.max.z)
			return false;
		if (max.z <= box.min.z)
			return false;
		return true;
	}

	bool inside(const boundingbox3d<T>& box) const
	{
		if (min.x < box.min.x)
			return false;
		if (max.x > box.max.x)
			return false;
		if (min.y < box.min.y)
			return false;
		if (max.y > box.max.y)
			return false;
		if (min.z < box.min.z)
			return false;
		if (max.z > box.max.z)
			return false;
		return true;
	}
};

typedef boundingbox3d<int> intbb3d;
typedef boundingbox3d<unsigned int> uintbb3d;
typedef boundingbox3d<float> floatbb3d;
typedef boundingbox3d<double> doublebb3d;
