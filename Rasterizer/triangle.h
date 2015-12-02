#pragma once

#include "../jmath/jmath.h"
#include "vertex.h"


template<typename T, typename V> class triangle
{
public:
	V v0, v1, v2;
public:
	triangle<T, V>(void) {}
	triangle<T, V>(V _v0, V _v1, V _v2) : v0(_v0), v1(_v1), v2(_v2) {}

	bool clip(void)
	{
		const float clipDistance = 1;

		if (v0.p.x < -clipDistance || v0.p.x > clipDistance)
			return true;
		if (v1.p.x < -clipDistance || v1.p.x > clipDistance)
			return true;
		if (v2.p.x < -clipDistance || v2.p.x > clipDistance)
			return true;
		if (v0.p.y < -clipDistance || v0.p.y > clipDistance)
			return true;
		if (v1.p.y < -clipDistance || v1.p.y > clipDistance)
			return true;
		if (v2.p.y < -clipDistance || v2.p.y > clipDistance)
			return true;
		if (v0.p.z < -clipDistance || v0.p.z > clipDistance)
			return true;
#if 1
		if (v1.p.z < -clipDistance || v1.p.z > clipDistance)
			return true;
		if (v2.p.z < -clipDistance || v2.p.z > clipDistance)
			return true;
#endif
		return false;
	}

	void transform(matrix4x4<T>& transform)
	{
		v0.p = transform.transform(v0.p);
		v1.p = transform.transform(v1.p);
		v2.p = transform.transform(v2.p);
	}

	void setup(vector3<T>& e0, vector3<T>& e1, vector3<T>& e2, T& doubleArea) const
	{
		e0 = edge(v1.p, v0.p);
		e1 = edge(v2.p, v1.p);
		e2 = edge(v0.p, v2.p);
		doubleArea = e0.z + e1.z + e2.z;
	}
};

typedef triangle<float, floatvpnt> floatt;
typedef triangle<float, floatvpc> floattc;
typedef triangle<float, floatvpn> floattn;

#if 0
template<typename T> class triangle
{
public:
	vertexp<T> v0, v1, v2;
public:
	triangle<T>(void) {}
	triangle<T>(vector3<T> _v0, vector3<T> _v1, vector3<T> _v2) : v0(_v0), v1(_v1), v2(_v2) {}
	triangle<T>(vertexp<T> _v0, vertexp<T> _v1, vertexp<T> _v2) : v0(_v0), v1(_v1), v2(_v2) {}
};


template<typename T> class trianglec
	: public triangle<T>
{
public:
	vertexpc<T> vc0, vc1, vc2;
public:
	trianglec<T>(void) {}
	trianglec<T>(vertexpc<T> _vc0, vertexpc<T> _vc1, vertexpc<T> _vc2) : vc0(_vc0), vc1(_vc1), vc2(_vc2) {}

	bool clip(void)
	{
		const float clipDistance = 1;

		if (vc0.p.x < -clipDistance || vc0.p.x > clipDistance)
			return true;
		if (vc1.p.x < -clipDistance || vc1.p.x > clipDistance)
			return true;
		if (vc2.p.x < -clipDistance || vc2.p.x > clipDistance)
			return true;
		if (vc0.p.y < -clipDistance || vc0.p.y > clipDistance)
			return true;
		if (vc1.p.y < -clipDistance || vc1.p.y > clipDistance)
			return true;
		if (vc2.p.y < -clipDistance || vc2.p.y > clipDistance)
			return true;
		if (vc0.p.z < -clipDistance || vc0.p.z > clipDistance)
			return true;
#if 1
		if (vc1.p.z < -clipDistance || vc1.p.z > clipDistance)
			return true;
		if (vc2.p.z < -clipDistance || vc2.p.z > clipDistance)
			return true;
#endif

		return false;
	}

	void transform(matrix4x4<T>& transform)
	{
		vc0.p = transform.transform(vc0.p);
		vc1.p = transform.transform(vc1.p);
		vc2.p = transform.transform(vc2.p);
	}

	void setup(vector3<T>& e0, vector3<T>& e1, vector3<T>& e2, T& doubleArea) const
	{
		e0 = edge(vc1.p, vc0.p);
		e1 = edge(vc2.p, vc1.p);
		e2 = edge(vc0.p, vc2.p);
		doubleArea = e0.z + e1.z + e2.z;
	}
};


template<typename T> class trianglen
{
public:
	vertexpn<T> vn0, vn1, vn2;
public:
	trianglen<T>(void) {}
	trianglen<T>(vertexpn<T> _vn0, vertexpn<T> _vn1, vertexpn<T> _vn2) : vn0(_vn0), vn1(_vn1), vn2(_vn2) {}
};


typedef triangle<float> floatt;
typedef trianglec<float> floattc;
typedef trianglen<float> floattn;
typedef triangle<double> doublet;
typedef trianglec<double> doubletc;
typedef trianglen<double> doubletn;

#endif