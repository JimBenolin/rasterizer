#pragma once

#include "vector3.h"


template<typename T> class vector4
{
public:
	union
	{
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		T mData[4];
	};

public:
	//  constructors
	vector4<T>() {}
	vector4<T>(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	vector4<T>(const vector2<T>& v, T _z, T _w) : x(v.x), y(v.y), z(_z), w(_w) {}
	vector4<T>(const vector3<T>& v, T _w) : x(v.x), y(v.y), z(v.z), w(_w) {}
//	vector4<T>(const vertex<T>& v) : x(v.v.x), y(v.v.y), z(v.v.z), w(T(1)) {}
	explicit vector4<T>(const T* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3]) {}
	explicit vector4<T>(T v) : x(v), y(v), z(v), w(v) {}

	//  element access
	T operator[] (int i) const { assert(0 <= i && i < 4); return mData[i]; }
	T& operator[](int i) { assert(0 <= i && i < 4); return mData[i]; }
	operator T*() { return mData; }
	operator const T*() const { return mData; }
	vector2<T> xy() const { return vector2<T>(x, y); }
	vector3<T> xyz() const { return vector3<T>(x, y, z); }
	vector3<T> xyw() const { return vector3<T>(x, y, w); }

	//  boolean operators
	bool operator== (const vector4<T>& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator!= (const vector4<T>& v) const { return !(*this == v); }
	bool operator< (const vector4<T>&v ) const { if (x != v.x) return x < v.x; else if (y != v.y) return y < v.y; else if (z != v.z) return z < v.z; else return w < v.w; }

	//  element-wise arithmetic operators
	vector4<T> operator+(T s) const { return vector4<T>(x + s, y + s, z + s, w + s); }
	vector4<T> operator-(T s) const { return vector4<T>(x - s, y - s, z - s, w - s); }
	vector4<T> operator*(T s) const { return vector4<T>(x * s, y * s, z * s, w * s); }
	vector4<T> operator/(T s) const { T inv = 1.f / s; return vector4<T>(x * inv, y * inv, z * inv, w * inv); }
	vector4<T> operator+(const vector4<T>& v) const { return vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w); }
	vector4<T> operator-(const vector4<T>& v) const { return vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w); }
	vector4<T> operator*(const vector4<T>& v) const { return vector4<T>(x * v.x, y * v.y, z * v.z, w * v.w); }
	vector4<T>& operator+=(T s) { x += s; y += s; z += s; w += s; return *this; }
	vector4<T>& operator-=(T s) { x -= s; y -= s; z -= s; w -= s; return *this; }
	vector4<T>& operator*=(T s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	vector4<T>& operator/=(T s) { T inv = 1.f / s; x *= inv; y *= inv; z *= inv; w *= inv; return *this; }
	vector4<T>& operator+=(const vector4<T>& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	vector4<T>& operator-=(const vector4<T>& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	vector4<T>& operator*=(const vector4<T>& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	vector4<T> operator-(void) const { return vector4<T>(-x, -y, -z, -w); }

	//  element-wise arithmetic scalar-tuple operations
	friend vector4<T> operator+(T s, const vector4<T>& v) { return v + s; }
	friend vector4<T> operator-(T s, const vector4<T>& v) { return vector4<T>(s - v.x, s - v.y, s - v.z, s - v.w); }
	friend vector4<T> operator*(T s, const vector4<T>& v) { return v * s; }
	friend vector4<T> operator/(T s, const vector4<T>& v) { return vector4<T>(s / v.x, s / v.y, s / v.z, s / v.w); }

	//  geometric functions
	T lengthSquared(void) const { return x * x + y * y + z * z + w * w; }
	T length(void) const { return std::sqrt(lengthSquared()); }
	vector4<T> normalized(void) const { return (*this) / length(); }
	void normalize(void) { *this = (*this) / length(); }
	T dot(const vector4<T>& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
	friend T dot(const vector4<T>& v1, const vector4<T>& v2) { return v1.dot(v2); }

	void abs(void) { x = std.abs(x); y = std::abs(y); z = std::abs(z); w = std::abs(w); }
	friend vector4<T> abs(const vector4<T>& v) { return vector4<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }
	friend vector4<T> min(const vector4<T>& lhs, const vector4<T>& rhs) { return vector4<T>(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z), std::min(lhs.w, rhs.w)); }
	friend vector4<T> max(const vector4<T>& lhs, const vector4<T>& rhs) { return vector4<T>(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z), std::max(lhs.w, rhs.w)); }
	void clamp(const T min, const T max) { x = std::max(min, std::min(x, max)); y = std::max(min, std::min(y, max)); z = std::max(min, std::min(z, max)); w = std::max(min, std::min(w, max)); }
	void clamp(const vector4<T>& min, const vector4<T>& max) { x = std::max(min.x, std::min(x, max.x)); y = std::max(min.y, std::min(y, max.y)); z = std::max(min.z, std::min(z, max.z)); w = std::max(min.w, std::min(w, max.w)); }
	friend vector4<T> clamp(const vector4<T>& value, const T min, const T max) { return vector4<T>(std::max(min, std::min(value.x, max)), std::max(min, std::min(value.y, max)), std::max(min, std::min(value.z, max)), std::max(min, std::min(value.w, max))); }
	friend vector4<T> clamp(const vector4<T>& value, const vector4<T>& min, const vector4<T>& max) { return vector4<T>(std::max(min.x, std::min(value.x, max.x)), std::max(min.y, std::min(value.y, max.y)), std::max(min.z, std::min(value.z, max.z)), std::max(min.w, std::min(value.w, max.w))); }

	//  debug
	friend std::ostream& operator<<(std::ostream& os, const vector4<T>& v) { os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]"; return os; }
	friend std::istream& operator>>(std::istream& is, vector4<T>& v) { is >> v.x >> v.y >> v.z >> v.w; return is; }
};

typedef vector4<float> float4;
typedef vector4<double> double4;
typedef vector4<uint8_t> ubyte4;
typedef vector4<uint16_t> uint4;
