#pragma once

#include "vector4.h"
#include "matrix3x3.h"

template<typename T> class matrix4x4
{
	union
	{
		struct
		{
			T _11, _12, _13, _14;
			T _21, _22, _23, _24;
			T _31, _32, _33, _34;
			T _41, _42, _43, _44;
		};
		struct
		{
			vector4<T> m[4];
		};
		T mData[4][4];
	};

public:
	//  Constructors
	matrix4x4<T>() {}
	matrix4x4<T>(const vector4<T>& v0, const vector4<T>& v1, const vector4<T>& v2, const vector4<T>& v3, bool columnVectors = false) { if (columnVectors) { setColumns(v0, v1, v2, v3); } else { setRows(v0, v1, v2, v3); } }
	matrix4x4<T>(T _11, T _12, T _13, T _14, T _21, T _22, T _23, T _24, T _31, T _32, T _33, T _34, T _41, T _42, T _43, T _44) : _11(_11), _12(_12), _13(_13), _14(_14), _21(_21), _22(_22), _23(_23), _24(_24), _31(_31), _32(_32), _33(_33), _34(_34), _41(_41), _42(_42), _43(_43), _44(_44) {}
	explicit matrix4x4<T>(const T* elements) { assert(elements); memcpy(mData, elements, sizeof(mData)); }

	//  element access
	vector4<T> operator[](int row) const { assert(0 <= row && row < 4); return m[row]; }
	vector4<T>& operator[](int row) { assert(0 <= row && row < 4); return m[row]; }
	T& get(int row, int col) { assert(0 <= row && row < 4); assert(0 <= col && col < 4); return m[row][col]; }
	const T& get(int row, int col) const { assert(0 <= row && row < 4); assert(0 <= col && col < 4); return m[row][col]; }
	operator T*() { return mData; };
	operator const T*() const { return mData; };

	//  row/column access
	vector4<T> getRow(int row) const { assert(row >= 0 && row < 4); return m[row]; }
	vector4<T> getColumn(int col) const { assert(col >= 0 && col < 4); return vector4<T>(m[0][col], m[1][col], m[2][col], m[3][col]); }
	matrix3x3<T> getSubMatrix(void) const { return matrix3x3<T>(m[0].xyz(), m[1].xyz(), m[2].xyz()); }
	void setRow(int row, const vector4<T>& v) { assert(row >= 0 && row < 4); m[row] = v; }
	void setRows(const vector4<T>& v0, const vector4<T>& v1, const vector4<T>& v2, const vector4<T>& v3) { setRow(0, v0); setRow(1, v1); setRow(2, v2); setRow(3, v3); }
	void setColumn(int col, const vector4<T>& v) { assert(col >= 0 && col < 4); m[0][col] = v.x; m[1][col] = v.y; m[2][col] = v.z; m[3][col] = v.w; }
	void setColumns(const vector4<T>& v0, const vector4<T>& v1, const vector4<T>& v2, const vector4<T>& v3) { setColumn(0, v0); setColumn(1, v1); setColumn(2, v2);; setColumn(3, v3); }

	//  setup matrix
	void setZero(void) { memset(mData, 0, sizeof(mData)); }
	void setIdentity() { setZero(); m[0][0] = m[1][1] = m[2][2] = m[3][3] = T(1); }
	void setScale(T s) { setZero(); m[0][0] = m[1][1] = m[2][2] = s;  m[3][3] = T(1); }
	void setScale(T sx, T sy, T sz) { setZero(); m[0][0] = sx; m[1][1] = sy; m[2][2] = sz; m[3][3] = T(1); }
	void setScale(const vector3<T>& s) { setScale(s.x, s.y, s.z); }
	void setTranslation(T tx, T ty, T tz) { setIdentity(); m[0][3] = tx; m[1][3] = ty; m[2][3] = tz; }
	void setTranslation(const vector3<T>& t) { setTranslation(t.x, t.y, t.z); }
	void setRotateAxis(const vector3<T>& v, T a) { T sinA = sin(a), cosA = cos(a); T iCosA = 1 - cosA; setZero(); m[0] = vector4<T>(cosA + v.x * v.x* iCosA, v.x * v.y * iCosA - v.z * sinA, v.x * v.z * iCosA + v.y * sinA, T(0)); m[1] = vector4<T>(v.x * v.y * iCosA + v.z * sinA, cosA + v.y * v.y * iCosA, v.y * v.z * iCosA - v.x * sinA, T(0)); m[2] = vector4<T>(v.x * v.z * iCosA - v.y * sinA, v.y * v.z * iCosA + v.x * sinA, cosA + v.z * v.z * iCosA, T(0)); m[3][3] = T(1); }
	void setRotateAxisX(T a) { T sinA = sin(a), cosA = cos(a); setZero(); m[0][0] = T(1); m[1][1] = cosA; m[1][2] = -sinA; m[2][1] = sinA; m[2][2] = cosA; m[3][3] = T(1); }
	void setRotateAxisY(T a) { T sinA = sin(a), cosA = cos(a); setZero(); m[0][0] = cosA; m[0][2] = sinA; m[1][1] = T(1); m[2][0] = -sinA; m[2][2] = cosA; m[3][3] = T(1); }
	void setRotateAxisZ(T a) { T sinA = sin(a), cosA = cos(a); setZero(); m[0][0] = cosA; m[0][1] = -sinA; m[1][0] = sinA; m[1][1] = cosA; m[2][2] = T(1); m[3][3] = T(1); }

	void setCameraLookAtRH(const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up)
	{
		vector3<T> zAxis = (eye - target).normalized();  //  the "forward" vector.
		vector3<T> xAxis = up.cross(zAxis).normalized();  //  the "right" vector.
		vector3<T> yAxis = zAxis.cross(xAxis);  //  the "up" vector.
		matrix4x4<T> orientation(vector4<T>(xAxis, 0), vector4<T>(yAxis, 0), vector4<T>(zAxis, 0), vector4<T>(0, 0, 0, 1));
		*this = orientation * translation(-eye);
	}

	void setCameraFirstPersonRH(const vector3<T>& eye, T pitch, T yaw)
	{
		//  Pitch should be in the range of [-90 ... 90] degrees and yaw should be in the range of [0 ... 360] degrees.
		T cosPitch = cos(pitch), sinPitch = sin(pitch), cosYaw = cos(yaw), sinYaw = sin(yaw);

		vector3<T> xaxis(cosYaw, 0, -sinYaw);
		vector3<T> yaxis(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
		vector3<T> zaxis(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

		matrix4x4<T> orientation(vector4<T>(xaxis, 0), vector4<T>(yaxis, 0), vector4<T>(zaxis, 0), vector4<T>(0, 0, 0, 1));

		*this = orientation * translation(-eye);
	}

	void setCameraArcBallRH(const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up, T pitch, T yaw)
	{

		T cosPitch = cos(pitch), sinPitch = sin(pitch), cosYaw = cos(yaw), sinYaw = sin(yaw);

		vector3<T> xaxis(cosYaw, 0, -sinYaw);
		vector3<T> yaxis(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
		vector3<T> zaxis(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

		matrix4x4<T> orientation(vector4<T>(xaxis, 0), vector4<T>(yaxis, 0), vector4<T>(zaxis, 0), vector4<T>(0, 0, 0, 1));

	}

	void setProjectionPerspectiveB(T n, T f, T t, T b, T l, T r)
	{
		T nn = 2 * n;
		T rml = r - l;
		T rpl = r + l;
		T tmb = t - b;
		T tpb = t + b;
		T fmn = f - n;
		T fpn = f + n;
		*this = matrix4x4(nn / rml, 0, -rpl / rml, 0,
			0, nn / tmb, -tpb / tmb, 0,
			0, 0, fpn / fmn, T(-2) * f * n / fmn,
			0, 0, T(1), 0);
	}

	void setProjectionPerspectiveNW(T fov, T width, T height, T zNear, T zFar)
	{
		T ar = width / height;
		T tanHalfFov = tan(fov / T(2));
		T zRange = zNear - zFar;
		*this = matrix4x4(T(1) / (tanHalfFov * ar), 0, 0, 0,
			0, T(1) / tanHalfFov, 0, 0,
			0, 0, (zNear - zFar) / (zNear + zFar), T(2) * zFar * zNear / (zNear + zFar),
			0, 0, T(1), 0);
	}
	void setProjectionPerspective(T fov, T width, T height, T zNear, T zFar)
	{
		T ar = width / height;
		T tanHalfFov = tan(fov / T(2));
		T zRange = zNear - zFar;
		*this = matrix4x4(-T(1) / (tanHalfFov * ar), 0, 0, 0,
			0, T(1) / tanHalfFov, 0, 0,
			0, 0, -(zNear + zFar) / zRange, T(2) * zFar * zNear / zRange,
			0, 0, T(1), 0);
	}


	//  standard matrix operations
	void transpose(void) { setColumns(getRow(0), getRow(1), getRow(2), getRow(3)); }
	void transpose(matrix4x4<T>& result) const { result = *this; result.transpose(); }
	matrix4x4<T> transposed() const { matrix4x4<T> result(*this); result.transpose(); return result; }
//	void invert(void) { T det = determinant(); *this = matrix4x4<T>(m[1][1] * m[2][2] - m[1][2] * m[2][1], m[0][2] * m[2][1] - m[0][1] * m[2][2], m[0][1] * m[1][2] - m[0][2] * m[1][1], m[1][2] * m[2][0] - m[1][0] * m[2][2], m[0][0] * m[2][2] - m[0][2] * m[2][0], m[0][2] * m[1][0] - m[0][0] * m[1][2], m[1][0] * m[2][1] - m[1][1] * m[2][0], m[0][1] * m[2][0] - m[0][0] * m[2][1], m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det; }
//	void invert(matrix4x4<T>& result) const { result = *this; result.invert(); }
//	matrix4x4<T> inverted(void) const { matrix2x2<T> result(*this); result.invert(); return result; }
//	T determinant(void) const { return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) + m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]); }

	//  arithmetic operations
	matrix4x4<T> operator+(const matrix4x4<T>& rhs) const { return matrix4x4<T>(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3]); }
	matrix4x4<T> operator-(const matrix4x4<T>& rhs) const { return matrix4x4<T>(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3]); }
	matrix4x4<T> operator*(const matrix4x4<T>& rhs) const { matrix4x4<T> M; for (int row = 0; row < 4; row++) for (int col = 0; col < 4; col++) M[row][col] = dot(getRow(row), rhs.getColumn(col)); return M; }
	matrix4x4<T>& operator+=(const matrix4x4<T>& rhs) { return *this = *this + rhs; }
	matrix4x4<T>& operator-=(const matrix4x4<T>& rhs) { return *this = *this - rhs; }
	matrix4x4<T>& operator*=(const matrix4x4<T>& rhs) { return *this = *this * rhs; }
	matrix4x4<T> operator+(const T v) const { return matrix4x4<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v); }
	matrix4x4<T> operator-(const T v) const { return matrix4x4<T>(m[0] - v, m[1] - v, m[2] - v, m[3] - v); }
	matrix4x4<T> operator*(const T v) const { return matrix4x4<T>(m[0] * v, m[1] * v, m[2] * v, m[3] * v); }
	matrix4x4<T> operator/(const T v) const { return *this * (T(1) / v); }
	matrix4x4<T>& operator+=(const T v) { return *this = *this + v; }
	matrix4x4<T>& operator-=(const T v) { return *this = *this - v; }
	matrix4x4<T>& operator*=(const T v) { return *this = *this * v; }
	matrix4x4<T>& operator/=(const T v) { return *this = *this / v; }
	friend matrix4x4<T> operator+(const T v, const matrix4x4<T>& rhs) { return rhs + v; }
	friend matrix4x4<T> operator*(const T v, const matrix4x4<T>& rhs) { return rhs * v; }

	//  transforms
	vector4<T> operator*(const vector4<T>& v) const { return vector4<T>(getRow(0).dot(v), getRow(1).dot(v), getRow(2).dot(v), getRow(3).dot(v)); }
	vector4<T> operator*(const vector3<T>& v) const { return vector3<T>(getRow(0).xyz().dot(v), getRow(1).xyz().dot(v), getRow(2).xyz().dot(v)); }
	vector4<T> transform(const vector4<T>& v) const { return *this * v; }
//	vector4<T> transform(const vertex<T>& v) const { vector4<T> tr = *this * vector4<T>(v); if (tr.w != T(0)) tr /= tr.w; return tr; }
	vector3<T> transform(const vector3<T>& v) const { vector4<T> tr = *this * vector4<T>(v, T(1)); if (tr.w != T(0)) tr /= tr.w; return tr.xyz(); }
	void transform(const vector4<T>& v, vector4<T>& dst) const { dst = transform(v); }
	void transform(const vector3<T>& v, vector3<T>& dst) const { dst = transform(v); }
	friend vector4<T> operator*(const vector4<T> &v, const matrix4x4<T>& M) { return M.transform(v); }
	friend vector3<T> operator*(const vector3<T> &v, const matrix4x4<T>& M) { return M.transform(v); }

	//  debug
	friend std::ostream& operator<<(std::ostream& os, const matrix4x4<T>& m) { os << "[ " << m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << " ]"; return os; }
	friend std::istream& operator>>(std::istream& is, matrix4x4<T>& m) { is >> m[0] >> m[1] >> m[2] >> m[2]; return is; }

	//  statics
	static matrix4x4<T> zero(void) { matrix4x4<T> result; result.setZero(); return result; }
	static matrix4x4<T> identity(void) { matrix4x4<T> result; result.setIdentity(); return result; }
	static matrix4x4<T> scale(T s) { matrix4x4<T> result; result.setScale(s); return result; }
	static matrix4x4<T> scale(T sx, T sy, T sz) { matrix4x4<T> result; result.setScale(sx, sy, sz); return result; }
	static matrix4x4<T> scale(const vector3<T>& s) { matrix4x4<T> result; result.setScale(s); return result; }
	static matrix4x4<T> translation(T tx, T ty, T tz) { matrix4x4<T> result; result.setTranslation(tx, ty, tz); return result; }
	static matrix4x4<T> translation(const vector3<T>& t) { matrix4x4<T> result; result.setTranslation(t); return result; }
	static matrix4x4<T> rotateAxis(const vector3<T>& v, T a) { matrix4x4<T> result; result.setRotateAxis(v, a); return result; }
	static matrix4x4<T> rotateAxisX(T a) { matrix4x4<T> result; result.setRotateAxisX(a); return result; }
	static matrix4x4<T> rotateAxisY(T a) { matrix4x4<T> result; result.setRotateAxisY(a); return result; }
	static matrix4x4<T> rotateAxisZ(T a) { matrix4x4<T> result; result.setRotateAxisZ(a); return result; }
	static matrix4x4<T> cameraLookAtRH(const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up) { matrix4x4<T> result; result.setCameraLookAtRH(eye, target, up); return result; }
	static matrix4x4<T> cameraFirstPersonRH(const vector3<T>& eye, T pitch, T yaw) { matrix4x4<T> result; result.setCameraFirstPersonRH(eye, pitch, yaw); return result; }
	static matrix4x4<T> projectionPerspectiveB(T n, T f, T t, T b, T l, T r) { matrix4x4<T> result; result.setProjectionPerspectiveB(n, f, t, b, l, r); return result; }
	static matrix4x4<T> projectionPerspective(T fov, T width, T height, T zNear, T zFar) { matrix4x4<T> result; result.setProjectionPerspective(fov, width, height, zNear, zFar); return result; }
};

typedef matrix4x4<float> float4x4;
typedef matrix4x4<double> double4x4;
