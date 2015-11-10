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
	: public vertex<T>
{
public:
	vector4<T> c;
public:
	vertexc<T>(void) {}
	vertexc<T>(vector3<T> _v) : c(0) { v = _v; }
	vertexc<T>(vector3<T> _v, vector4<T> _c) : c(_c) { v = _v; }
};


template<typename T> class vertexn
	: public vertex<T>
{
public:
	vector3<T> n;
public:
	vertexn<T>(void) {}
	vertexn<T>(vector3<T> _v) : n(0) { v = _v; }
	vertexn<T>(vector3<T> _v, vector3<T> _n) : n(_n) { v = _v; }
};


template<typename T> class vertexcn
	: public vertex<T>
{
public:
	vector4<T> c;
	vector3<T> n;
public:
	vertexcn<T>(void) {}
	vertexcn<T>(vector3<T> _v) : v(_v), n(0) {}
	vertexcn<T>(vector3<T> _v, vector3<T> _n) : c(_c), n(_n) { v = _v; }
};


typedef vertex<float> floatv;
typedef vertexc<float> floatvc;
typedef vertexn<float> floatvn;
typedef vertexcn<float> floatvcn;
typedef vertex<double> doublev;
typedef vertexc<double> doublevc;
typedef vertexn<double> doublevn;
typedef vertexcn<double> doublevcn;
