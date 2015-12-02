#pragma once

#include "../jmath/jmath.h"


template<typename T> class vertexp
{
public:
	vector3<T> p;
public:
	vertexp<T>(void) {}
	vertexp<T>(vector3<T> _p) : p(_p) {}
};


template<typename T> class vertexpc
{
public:
	vector3<T> p;
	vector4<T> c;
public:
	vertexpc<T>(void) {}
	vertexpc<T>(vector3<T> _p) : p(_p), c(0) {}
	vertexpc<T>(vector3<T> _p, vector4<T> _c) : p(_p), c(_c) {}
};


template<typename T> class vertexpn
{
public:
	vector3<T> p;
	vector3<T> n;
public:
	vertexpn<T>(void) {}
	vertexpn<T>(vector3<T> _p) : p(_p), n(0) {}
	vertexpn<T>(vector3<T> _p, vector3<T> _n) : p(_p), n(_n) {}
};


template<typename T> class vertexpcn
{
public:
	vector3<T> p;
	vector4<T> c;
	vector3<T> n;
public:
	vertexpcn<T>(void) {}
	vertexpcn<T>(vector3<T> _p) : p(_p), c(0), n(0) {}
	vertexpcn<T>(vector3<T> _p, vector3<T> _n) : p(_p), c(_c), n(_n) {}
};


template<typename T> class vertexpnt
{
public:
	vector3<T> p;
	vector3<T> n;
	vector2<T> t;
public:
	vertexpnt<T>(void) {}
	vertexpnt<T>(vector3<T> _p) : p(_p), n(T(0)), t(T(0)) {}
	vertexpnt<T>(vector3<T> _p, vector3<T> _n, vector2<T> _t) : p(_p), n(_n), t(_t) {}
};


typedef vertexp<float> floatvp;
typedef vertexpc<float> floatvpc;
typedef vertexpn<float> floatvpn;
typedef vertexpcn<float> floatvpcn;
typedef vertexpnt<float> floatvpnt;
typedef vertexp<double> doublevp;
typedef vertexpc<double> doublevpc;
typedef vertexpn<double> doublevpn;
typedef vertexpcn<double> doublevpcn;
typedef vertexpnt<double> doublevpnt;
