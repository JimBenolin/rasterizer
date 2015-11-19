#pragma once

#include "../jmath/jmath.h"
#include "vertex.h"


template<typename T> class triangle
{
public:
	vertex<T> v0, v1, v2;
public:
	triangle<T>(void) {}
	triangle<T>(vector3<T> _v0, vector3<T> _v1, vector3<T> _v2) : v0(_v0), v1(_v1), v2(_v2) {}
	triangle<T>(vertex<T> _v0, vertex<T> _v1, vertex<T> _v2) : v0(_v0), v1(_v1), v2(_v2) {}
};


template<typename T> class trianglec
	: public triangle<T>
{
public:
	vertexc<T> vc0, vc1, vc2;
public:
	trianglec<T>(void) {}
	trianglec<T>(vertexc<T> _vc0, vertexc<T> _vc1, vertexc<T> _vc2) : vc0(_vc0), vc1(_vc1), vc2(_vc2) {}

	bool clip(void)
	{
		const float clipDistance = 1;

		if (vc0.v.x < -clipDistance || vc0.v.x > clipDistance)
			return true;
		if (vc1.v.x < -clipDistance || vc1.v.x > clipDistance)
			return true;
		if (vc2.v.x < -clipDistance || vc2.v.x > clipDistance)
			return true;
		if (vc0.v.y < -clipDistance || vc0.v.y > clipDistance)
			return true;
		if (vc1.v.y < -clipDistance || vc1.v.y > clipDistance)
			return true;
		if (vc2.v.y < -clipDistance || vc2.v.y > clipDistance)
			return true;
		if (vc0.v.z < -clipDistance || vc0.v.z > clipDistance)
			return true;
#if 1
		if (vc1.v.z < -clipDistance || vc1.v.z > clipDistance)
			return true;
		if (vc2.v.z < -clipDistance || vc2.v.z > clipDistance)
			return true;
#endif

		return false;
	}

	void transform(matrix4x4<T>& transform)
	{
		vc0.v = transform.transform(vc0.v);
		vc1.v = transform.transform(vc1.v);
		vc2.v = transform.transform(vc2.v);
	}

	void setup(vector3<T>& e0, vector3<T>& e1, vector3<T>& e2, T& doubleArea) const
	{
		e0 = edge(vc1.v, vc0.v);
		e1 = edge(vc2.v, vc1.v);
		e2 = edge(vc0.v, vc2.v);
		doubleArea = e0.z + e1.z + e2.z;
	}
};


template<typename T> class trianglen
{
public:
	vertexn<T> vn0, vn1, vn2;
public:
	trianglen<T>(void) {}
	trianglen<T>(vertexn<T> _vn0, vertexn<T> _vn1, vertexn<T> _vn2) : vn0(_vn0), vn1(_vn1), vn2(_vn2) {}
};


typedef triangle<float> floatt;
typedef trianglec<float> floattc;
typedef trianglen<float> floattn;
typedef triangle<double> doublet;
typedef trianglec<double> doubletc;
typedef trianglen<double> doubletn;
