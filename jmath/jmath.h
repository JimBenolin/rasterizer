#pragma once

#include <cmath>
#include <algorithm>

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

#include "matrix2x2.h"
#include "matrix3x3.h"
#include "matrix4x4.h"

#include "boundingbox.h"

namespace jmath
{
	template<typename T>
	T clamp(const T& value, const T& min, const T& max)
	{
		return std::min(max, std::max(value, min));
	}
}

#if 0
class float4x4
{
public:
	/// Setup a matrix for planar reflection (mirroring) about a plane with
	/// origin p and normal n.
	void SetReflect(const float3 &p, const float3 &n);

	/// Setup a left-handed (LH) view matrix for a camera located at \c eye, looking at the
	/// point \c at, and with up vector \c up.
	void SetLookAtLH(const float3 &eye, const float3 &at, const float3 &up);

	/// Setup a right-handed (RH) view matrix for a camera located at \c eye, looking at the
	/// point \c at, and with up vector \c up.
	void SetLookAtRH(const float3 &eye, const float3 &at, const float3 &up);

	/// Setup a left-handed (LH) view matrix.
	/// \deprecated Use SetLookAtLH instead.
	void SetLookAt(const float3 &eye, const float3 &at, const float3 &up) { SetLookAtLH(eye, at, up); }

	/// Setup a view matrix for a camera located at (ex,ey,ez), looking at the
	/// point (ax,ay,az), and with up vector (ux,uy,uz).
	/// \deprecated Use SetLookAtLH instead.
	void SetLookAt(float ex, float ey, float ez,
		float ax, float ay, float az,
		float ux, float uy, float uz) {
		SetLookAt(float3(ex, ey, ez), float3(ax, ay, az), float3(ux, uy, uz));
	}

	/// Setup left-handed projection matrix based on field-of-view.
	/// \param fovy_rad Vertical field-of-view in radians.
	/// \param aspect Aspect ratio (width/height).
	/// \param near Z-value of near plane.
	/// \param far Z-value of far plane.
	void SetPerspectiveFovLH(float fovy_rad, float aspect, float near, float far);

	/// Setup right-handed projection matrix based on field-of-view.
	/// \param fovy_rad Vertical field-of-view in radians.
	/// \param aspect Aspect ratio (width/height).
	/// \param near Z-value of near plane.
	/// \param far Z-value of far plane.
	void SetPerspectiveFovRH(float fovy_rad, float aspect, float near, float far);

	/// Setup view matrix for the given face of a cube map centered at \c p.
	/// \todo Verify that this follows expected conventions.
	/// \param p Origin of cube map.
	/// \param axis Number of the axis (0=x, 1=y, 2=z).
	/// \param sign Look in the negative (sign=0) or positive (sign=1)direction.
	void SetCubeMapView(const float3 &p, int axis, int sign);

	/// \name Point/Vector transformations
	//@{

	/// Transforms the vector v by the matrix and returns the result.
	/// This computes v' = v * M, where v is a row vector.
	float4 Transform(const float4 &v) const {
		return float4(
			m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
			m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
			m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
			m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
			);
	}

	/// Transforms the vector v by the matrix and returns the result in \c dst.
	/// This computes v' = v * M, where v is a row vector.
	void Transform(const float4 &v, float4 &dst) const {
		dst = Transform(v);
	}

	/// Transforms a 3D vector v by the matrix and returns the result.
	/// This computes v' = v * M, where v is a row vector v = [x y z 0].
	/// \note This assumes an implicit w = 0.
	float3 TransformVector(const float3 &v) const {
		return float3(
			m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2],
			m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2],
			m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]
			);
	}

	/// Transforms a 3D vector v by the matrix and returns the result in \c dst.
	/// This computes v' = v * M, where v is a row vector v = [x y z 0].
	/// \note This assumes an implicit w = 0.
	void TransformVector(const float3 &v, float3 &dst) const {
		dst = TransformVector(v);
	}

	/// Transforms a 3D point p by the matrix and returns the result.
	/// This computes v' = v * M, where v is a row vector v = [x y z 1],
	/// and then returns [vx vy vz] / vw.
	/// \note This assumes an implicit w = 1 and performs a division-by-w.
	float3 TransformPoint(const float3 &p) const {
		float3 result;
		result[0] = m[0][0] * p[0] + m[1][0] * p[1] + m[2][0] * p[2] + m[3][0];
		result[1] = m[0][1] * p[0] + m[1][1] * p[1] + m[2][1] * p[2] + m[3][1];
		result[2] = m[0][2] * p[0] + m[1][2] * p[1] + m[2][2] * p[2] + m[3][2];
		float w = m[0][3] * p[0] + m[1][3] * p[1] + m[2][3] * p[2] + m[3][3];
		if (w != 1.f) {
			result /= w;
		}
		return result;
	}

	/// Transforms a 3D point p by the matrix and returns the result in \c dst.
	/// This computes v' = v * M, where v is a row vector v = [x y z 1],
	/// and then returns [vx vy vz] / vw.
	/// \note This assumes an implicit w = 1 and performs a division-by-w.
	void TransformPoint(const float3 &p, float3 &dst) const {
		dst = TransformPoint(p);
	}

	//@}

	// Friends

	/// \name Transformation
	//@{

	/// Transforms the vector v (row vector) by the matrix M.
	/// This computes v' = v * M, where v is a row vector.
	friend float4 operator* (const float4 &v, const float4x4 &M) {
		return M.Transform(v);
	}

	/// Transforms the vector v (column vector) by the matrix M.
	/// This computes v' = M * v, where v is a column vector.
	friend float4 operator* (const float4x4 &M, const float4 &v) {
		return float4(
			M.m[0][0] * v[0] + M.m[0][1] * v[1] + M.m[0][2] * v[2] + M.m[0][3] * v[3],
			M.m[1][0] * v[0] + M.m[1][1] * v[1] + M.m[1][2] * v[2] + M.m[1][3] * v[3],
			M.m[2][0] * v[0] + M.m[2][1] * v[1] + M.m[2][2] * v[2] + M.m[2][3] * v[3],
			M.m[3][0] * v[0] + M.m[3][1] * v[1] + M.m[3][2] * v[2] + M.m[3][3] * v[3]
			);
	}
};
#endif