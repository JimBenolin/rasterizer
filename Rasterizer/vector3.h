#pragma once

#include "vector2.h"


template<typename T> class vector3
{
public:
	union
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T u, v, w; };
		T mData[3];
	};

public:
	//  constructors
	vector3<T>() {}
	vector3<T>(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	vector3<T>(const vector2<T>& v, T _z) : x(v.x), y(v.y), z(_z) {}
	explicit vector3<T>(const T* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
	explicit vector3<T>(T v) : x(v), y(v), z(v) {}

	//  element access
	T operator[](int i) const { assert(0 <= i && i < 3); return mData[i]; }
	T& operator[](int i) { assert(0 <= i && i < 3); return mData[i]; }
	operator T*() { return mData; };
	operator const T*() const { return mData; };
	vector2<T> xy() const { return vector2<T>(x, y); }
	vector2<T> xz() const { return vector2<T>(x, z); }
	vector2<T> yz() const { return vector2<T>(y, z); }

	//  boolean operators
	bool operator==(const vector3<T>& v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const vector3<T>& v) const { return !(*this == v); }
	bool operator<(const vector3<T>& v) const { if (x != v.x) return x < v.x; else if (y != v.y) return y < v.y; else return z < v.z; }

	//  element-wise arithmetic operators
	vector3<T> operator+(T s) const { return vector3<T>(x + s, y + s, z + s); }
	vector3<T> operator-(T s) const { return vector3<T>(x - s, y - s, z - s); }
	vector3<T> operator*(T s) const { return vector3<T>(x * s, y * s, z * s); }
	vector3<T> operator/(T s) const { T inv = 1.f / s; return vector3<T>(x * inv, y * inv, z * inv); }
	vector3<T> operator+(const vector3<T>& v) const { return vector3<T>(x + v.x, y + v.y, z + v.z); }
	vector3<T> operator-(const vector3<T>& v) const { return vector3<T>(x - v.x, y - v.y, z - v.z); }
	vector3<T> operator*(const vector3<T>& v) const { return vector3<T>(x * v.x, y * v.y, z * v.z); }
	vector3<T>& operator+=(T s) { x += s; y += s; z += s; return *this; }
	vector3<T>& operator-=(T s) { x -= s; y -= s; z -= s; return *this; }
	vector3<T>& operator*=(T s) { x *= s; y *= s; z *= s; return *this; }
	vector3<T>& operator/=(T s) { T inv = 1.f / s; x *= inv; y *= inv; z *= inv; return *this; }
	vector3<T>& operator+=(const vector3<T>& v) { x += v.x; y += v.y; z += v.z; return *this; }
	vector3<T>& operator-=(const vector3<T>& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	vector3<T>& operator*=(const vector3<T>& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	vector3<T> operator-(void) const { return vector3<T>(-x, -y, -z); }

	//  element-wise arithmetic scalar-tuple operators
	friend vector3<T> operator+(T s, const vector3<T>& v) { return v + s; }
	friend vector3<T> operator-(T s, const vector3<T>& v) { return vector3<T>(s - v.x, s - v.y, s - v.z); }
	friend vector3<T> operator*(T s, const vector3<T>& v) { return v * s; }
	friend vector3<T> operator/(T s, const vector3<T>& v) { return vector3<T>(s / v.x, s / v.y, s / v.z); }

	//  geometric functions
	T lengthSquared(void) const { return x * x + y * y + z * z; }
	T length(void) const { return std::sqrt(lengthSquared()); }
	vector3<T> normalized(void) const { return (*this) / length(); }
	void normalize(void) { *this = (*this) / length(); }
	T dot(const vector3<T>& v) const { return x * v.x + y * v.y + z * v.z; }
	friend T dot(const vector3<T>& v1, const vector3<T>& v2) { return v1.dot(v2); }
	void abs(void) { x = std.abs(x); y = std::abs(y); z = std::abs(z); }
	friend vector3<T> abs(const vector3<T>& v) { return vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
	friend vector3<T> min(const vector3<T>& lhs, const vector3<T>& rhs) { return vector3<T>(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z)); }
	friend vector3<T> max(const vector3<T>& lhs, const vector3<T>& rhs) { return vector3<T>(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z)); }
	void clamp(const T min, const T max) { x = clamp<T>(x, min, max); y = clamp<T>(y, min, max); z = clamp<T>(z, min, max); }
	void clamp(const vector3<T>& min, const vector3<T>& max) { x = clamp<T>(x, min.x, max.x); y = clamp<T>(y, min.y, max.y); z = clamp<T>(z, min.z, max.z); }
	friend vector3<T> clamp(const vector3<T>& value, const T min, const T max) { return vector3<T>(clamp<T>(value.x, min, max), clamp<T>(value.y, min, max), clamp<T>(value.z, min, max)); }
	friend vector3<T> clamp(const vector3<T>& value, const vector3<T>& min, const vector3<T>& max) { return vector3<T>(clamp<T>(value.x, min.x, max.x), clamp<T>(value.y, min.y, max.y), clamp<T>(value.z, min.z, max.z)); }
	vector3<T> cross(const vector3<T>& v) const { return vector3<T>((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x)); }
	friend vector3<T> edge(const vector3<T>& v0, const vector3<T>& v1) { T A = v0.y - v1.y; T B = v1.x - v0.x; return vector3<T>(A, B, -(A * (v0.x + v1.x) + B * (v0.y + v1.y)) / T(2)); }
	friend vector3<T> cross(const vector3<T>& v1, const vector3<T>& v2) { return v1.cross(v2); }
	friend vector3<T> reflect(const vector3<T>& v, const vector3<T>& n) { return -v + 2.f * v.Dot(n) * n; }  //  reflects the vector v around the normal n (n must be normalized)
	friend T distanceSquared(const vector3<T>& p1, const vector3<T>& p2) { return (p1 - p2).lengthSquared(); }
	friend T distance(const vector3<T>& p1, const vector3<T>& p2) { return (p1 - p2).length(); }

	//  debug
	friend std::ostream& operator<<(std::ostream& os, const vector3<T>& v) { os << "[" << v.x << ", " << v.y << ", " << v.z << "]"; return os; }
	friend std::istream& operator>>(std::istream& is, vector3<T>& v) { is >> v.x >> v.y >> v.z; return is; }
};

typedef vector3<float> float3;
typedef vector3<double> double3;
typedef vector3<uint16_t> uint3;
typedef vector3<uint8_t> ubyte3;
