#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>


template<typename T> class vector2
{
public:
	union
	{
		struct { T x, y; };
		struct { T u, v; };
		T mData[2];
	};

public:
	//  constructors
	vector2<T>() {}
	vector2<T>(T _x, T _y) : x(_x), y(_y) {}
	explicit vector2<T>(const T* ptr) : x(ptr[0]), y(ptr[1]) {}
	explicit vector2<T>(T v) : x(v), y(v) {}

	//  element access
	T operator[](int i) const { assert(0 <= i && i < 2); return mData[i]; }
	T& operator[](int i) { assert(0 <= i && i < 2); return mData[i]; }
	operator T*() { return mData; };
	operator const T*() const { return mData; };

	//  boolean operators
	bool operator==(const vector2<T>& v) const { return x == v.x && y == v.y; }
	bool operator!=(const vector2<T>& v) const { return !(*this == v); }
	bool operator<(const vector2<T>& v) const { if (x != v.x) return x < v.x; else return y < v.y; }

	//  element-wise arithmetic operators
	vector2<T> operator+(T s) const { return vector2<T>(x + s, y + s); }
	vector2<T> operator-(T s) const { return vector2<T>(x - s, y - s); }
	vector2<T> operator*(T s) const { return vector2<T>(x * s, y * s); }
	vector2<T> operator/(T s) const { T inv = 1.f / s; return vector2<T>(x * inv, y * inv); }
	vector2<T> operator+(const vector2<T>& v) const { return vector2<T>(x + v.x, y + v.y); }
	vector2<T> operator-(const vector2<T>& v) const { return vector2<T>(x - v.x, y - v.y); }
	vector2<T> operator*(const vector2<T>& v) const { return vector2<T>(x * v.x, y * v.y); }
	vector2<T>& operator+=(T s) { x += s; y += s; return *this; }
	vector2<T>& operator-=(T s) { x -= s; y -= s; return *this; }
	vector2<T>& operator*=(T s) { x *= s; y *= s; return *this; }
	vector2<T>& operator/=(T s) { T inv = 1.f / s; x *= inv; y *= inv; return *this; }
	vector2<T>& operator+=(const vector2<T>& v) { x += v.x; y += v.y; return *this; }
	vector2<T>& operator-=(const vector2<T>& v) { x -= v.x; y -= v.y; return *this; }
	vector2<T>& operator*=(const vector2<T>& v) { x *= v.x; y *= v.y; return *this; }
	vector2<T> operator-(void) const { return vector2<T>(-x, -y); }

	//  element-wise arithmetic scalar-tuple operations
	friend vector2<T> operator+(T s, const vector2<T>& v) { return v + s; }
	friend vector2<T> operator-(T s, const vector2<T>& v) { return vector2<T>(s - v.x, s - v.y); }
	friend vector2<T> operator*(T s, const vector2<T>& v) { return v * s; }
	friend vector2<T> operator/(T s, const vector2<T>& v) { return vector2<T>(s / v.x, s / v.y); }

	//  geometric functions
	T lengthSquared(void) const { return x * x + y * y; }
	T length(void) const { return std::sqrt(lengthSquared()); }
	vector2<T> normalized(void) const { return (*this) / length(); }
	void normalize(void) { *this = (*this) / length(); }
	T dot(const vector2<T>& v) const { return x * v.x + y * v.y; }
	friend T dot(const vector2<T>& v1, const vector2<T>& v2) { return v1.dot(v2); }
	void abs(void) { x = std.abs(x); y = std::abs(y); }
	friend vector2<T> abs(const vector2<T>& v) { return vector2<T>(std::abs(v.x), std::abs(v.y)); }
	friend vector2<T> min(const vector2<T>& lhs, const vector2<T>& rhs) { return vector2<T>(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y)); }
	friend vector2<T> max(const vector2<T>& lhs, const vector2<T>& rhs) { return vector2<T>(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y)); }
	void clamp(const T min, const T max) { x = clamp<T>(x, min, max); y = clamp<T>(y, min, max); }
	void clamp(const vector2<T>& min, const vector2<T>& max) { x = clamp<T>(x, min.x, max.x); y = clamp<T>(y, min.y, max.y); }
	friend vector2<T> clamp(const vector2<T>& value, const T min, const T max) { return vector2<T>(clamp<T>(value.x, min, max), clamp<T>(value.y, min, max)); }
	friend vector2<T> clamp(const vector2<T>& value, const vector2<T>& min, const vector2<T>& max) { return vector2<T>(clamp<T>(value.x, min.x, max.x), clamp<T>(value.y, min.y, max.y)); }

	//  debug
	friend std::ostream& operator<<(std::ostream& os, const vector2<T>& v) { os << "[" << v.x << ", " << v.y << "]"; return os; }
	friend std::istream& operator>>(std::istream& is, vector2<T>& v) { is >> v.x >> v.y; return is; }
};

typedef vector2<uint8_t> ubyte2;
typedef vector2<int> int2;
typedef vector2<unsigned int> uint2;
typedef vector2<float> float2;
typedef vector2<double> double2;
