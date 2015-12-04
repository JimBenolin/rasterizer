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
typedef triangle<float, floatvpnt> floattnt;
