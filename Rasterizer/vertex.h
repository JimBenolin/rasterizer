#pragma once

#include "vector3.h"
#include "vector4.h"


template<typename T> class vertex
{
public:
	vector3<T> v;
public:
	vertex<T>(void) {}
	vertex<T>(vector3<T> _v) : v(_v) {}
};


template<typename T> class vertexc
{
public:
	vector3<T> v;
	vector4<T> c;
public:
	vertexc<T>(void) {}
	vertexc<T>(vector3<T> _v) : v(_v), c(0) {}
	vertexc<T>(vector3<T> _v, vector4<T> _c) : v(_v), c(_c) {}
};


template<typename T> class vertexn
{
public:
	vector3<T> v, n;
public:
	vertexn<T>(void) {}
	vertexn<T>(vector3<T> _v) : v(_v), n(0) {}
	vertexn<T>(vector3<T> _v, vector3<T> _n) : v(_v), n(_n) {}
};


typedef vertex<float> floatv;
typedef vertexc<float> floatvc;
typedef vertexn<float> floatvn;
typedef vertex<double> doublev;
typedef vertexc<double> doublevc;
typedef vertexn<double> doublevn;
