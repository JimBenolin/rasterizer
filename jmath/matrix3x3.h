#pragma once

#include "vector3.h"

template<typename T> class matrix3x3
{
	union
	{
		struct
		{
			T _11, _12, _13;
			T _21, _22, _23;
			T _31, _32, _33;
		};
		struct
		{
			vector3<T> m[3];
		};
		T mData[3][3];
	};

public:
	//  Constructors
	matrix3x3<T>() {}
	matrix3x3<T>(const vector3<T>& v0, const vector3<T>& v1, const vector3<T>& v2, bool columnVectors = false) { if (columnVectors) { setColumns(v0, v1, v2); } else { setRows(v0, v1, v2); } }
	matrix3x3<T>(T _11, T _12, T _13, T _21, T _22, T _23, T _31, T _32, T _33) : _11(_11), _12(_12), _13(_13), _21(_21), _22(_22), _23(_23), _31(_31), _32(_32), _33(_33) {}
	explicit matrix3x3<T>(const T* elements) { assert(elements); memcpy(mData, elements, sizeof(mData)); }

	//  element access
	vector3<T> operator[](int row) const { assert(0 <= row && row < 3); return m[row]; }
	vector3<T>& operator[](int row) { assert(0 <= row && row < 3); return m[row]; }
	T& get(int row, int col) { assert(0 <= row && row < 3); assert(0 <= col && col < 3); return m[row][col]; }
	const T& get(int row, int col) const { assert(0 <= row && row < 3); assert(0 <= col && col < 3); return m[row][col]; }
	operator T*() { return mData; };
	operator const T*() const { return mData; };

	//  row/column access
	vector3<T> getRow(int row) const { assert(row >= 0 && row < 3); return m[row]; }
	vector3<T> getColumn(int col) const { assert(col >= 0 && col < 3); return vector3<T>(m[0][col], m[1][col], m[2][col]); }
	void setRow(int row, const vector3<T>& v) { assert(row >= 0 && row < 3); m[row] = v; }
	void setRows(const vector3<T>& v0, const vector3<T>& v1, const vector3<T>& v2) { setRow(0, v0); setRow(1, v1); setRow(2, v2); }
	void setColumn(int col, const vector3<T>& v) { assert(col >= 0 && col < 3); m[0][col] = v.x; m[1][col] = v.y; m[2][col] = v.z; }
	void setColumns(const vector3<T>& v0, const vector3<T>& v1, const vector3<T>& v2) { setColumn(0, v0); setColumn(1, v1); setColumn(2, v2); }

	//  setup matrix
	void setZero(void) { memset(mData, 0, sizeof(mData)); }
	void setIdentity() { setZero(); m[0][0] = m[1][1] = m[2][2] = T(1); }
	void setScale(T s) { setZero(); m[0][0] = m[1][1] = m[2][2] = s; }
	void setScale(T sx, T sy, T sz) { setZero(); m[0][0] = sx; m[1][1] = sy; m[2][2] = sz; }
	void setScale(const vector3<T>& s) { setScale(s.x, s.y, s.z); }
	void setRotateAxis(const vector3<T>& v, T a) { T sinA = sin(a), cosA = cos(a); T iCosA = 1 - cosA; setZero(); m[0] = vector4<T>(cosA + v.x * v.x* iCosA, v.x * v.y * iCosA - v.z * sinA, v.x * v.z * iCosA + v.y * sinA, T(0)); m[1] = vector4<T>(v.x * v.y * iCosA + v.z * sinA, cosA + v.y * v.y * iCosA, v.y * v.z * iCosA - v.x * sinA, T(0)); m[2] = vector4<T>(v.x * v.z * iCosA - v.y * sinA, v.y * v.z * iCosA + v.x * sinA, cosA + v.z * v.z * iCosA, T(0)); }
	void setRotateAxisX(T a) { T sinA = sin(a), cosA = cos(a); setZero(); m[0][0] = T(1); m[1][1] = cosA; m[1][2] = -sinA; m[2][1] = sinA; m[2][2] = cosA; }
	void setRotateAxisY(T a) { T sinA = sin(a), cosA = cos(a); setZero(); m[0][0] = cosA; m[0][2] = sinA; m[1][1] = T(1); m[2][0] = -sinA; m[2][2] = cosA; }
	void setRotateAxisZ(T a) { T sinA = sin(a), cosA = cos(a); setZero(); m[0][0] = cosA; m[0][1] = -sinA; m[1][0] = sinA; m[1][1] = cosA; m[2][2] = T(1); }

	//  standard matrix operations
	void transpose(void) { setColumns(getRow(0), getRow(1), getRow(2)); }
	void transpose(matrix3x3<T>& result) const { result = *this; result.transpose(); }
	matrix3x3<T> transposed() const { matrix3x3<T> result(*this); result.transpose(); return result; }
	void invert(void) { T det = determinant(); *this = matrix3x3<T>(m[1][1] * m[2][2] - m[1][2] * m[2][1], m[0][2] * m[2][1] - m[0][1] * m[2][2], m[0][1] * m[1][2] - m[0][2] * m[1][1], m[1][2] * m[2][0] - m[1][0] * m[2][2], m[0][0] * m[2][2] - m[0][2] * m[2][0], m[0][2] * m[1][0] - m[0][0] * m[1][2], m[1][0] * m[2][1] - m[1][1] * m[2][0], m[0][1] * m[2][0] - m[0][0] * m[2][1], m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det; }
	void invert(matrix3x3<T>& result) const { result = *this; result.invert(); }
	matrix3x3<T> inverted(void) const { matrix2x2<T> result(*this); result.invert(); return result; }
	T determinant(void) const { return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) + m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]); }

	//  arithmetic operations
	matrix3x3<T> operator+(const matrix3x3<T>& rhs) const { return matrix3x3<T>(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2]); }
	matrix3x3<T> operator-(const matrix3x3<T>& rhs) const { return matrix3x3<T>(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2]); }
	matrix3x3<T> operator*(const matrix3x3<T>& rhs) const { matrix3x3<T> M; for (int row = 0; row < 3; row++) for (int col = 0; col < 3; col++) M[row][col] = dot(getRow(row), rhs.getColumn(col)); return M; }
	matrix3x3<T>& operator+=(const matrix3x3<T>& rhs) { return *this = *this + rhs; }
	matrix3x3<T>& operator-=(const matrix3x3<T>& rhs) { return *this = *this - rhs; }
	matrix3x3<T>& operator*=(const matrix3x3<T>& rhs) { return *this = *this * rhs; }
	matrix3x3<T> operator+(const T v) const { return matrix3x3<T>(m[0] + v, m[1] + v, m[2] + v); }
	matrix3x3<T> operator-(const T v) const { return matrix3x3<T>(m[0] - v, m[1] - v, m[2] - v); }
	matrix3x3<T> operator*(const T v) const { return matrix3x3<T>(m[0] * v, m[1] * v, m[2] * v); }
	matrix3x3<T> operator/(const T v) const { return *this * (T(1) / v); }
	matrix3x3<T>& operator+=(const T v) { return *this = *this + v; }
	matrix3x3<T>& operator-=(const T v) { return *this = *this - v; }
	matrix3x3<T>& operator*=(const T v) { return *this = *this * v; }
	matrix3x3<T>& operator/=(const T v) { return *this = *this / v; }
	friend matrix3x3<T> operator+(const T v, const matrix3x3<T>& rhs) { return rhs + v; }
	friend matrix3x3<T> operator*(const T v, const matrix3x3<T>& rhs) { return rhs * v; }

	//  transforms
	vector3<T> operator*(const vector3<T>& v) const { return vector3<T>(getColumn(0).dot(v), getColumn(1).dot(v), getColumn(2).dot(v)); }
	vector3<T> transform(const vector3<T>& v) const { return *this * v; }
	void transform(const vector3<T>& v, vector3<T>& dst) const { dst = transform(v); }
	friend vector3<T> operator*(const vector3<T> &v, const matrix3x3<T>& M) { M.transform(v); }

	//  debug
	friend std::ostream& operator<<(std::ostream& os, const matrix3x3<T>& m) { os << "[ " << m[0] << ", " << m[1] << ", " << m[2] << " ]"; return os; }
	friend std::istream& operator>>(std::istream& is, matrix3x3<T>& m) { is >> m[0] >> m[1] >> m[2]; return is; }

	//  statics
	static matrix3x3<T> zero(void) { matrix3x3<T> result; result.setZero(); return result; }
	static matrix3x3<T> identity(void) { matrix3x3<T> result; result.setIdentity(); return result; }
	static matrix3x3<T> scale(T s) { matrix3x3<T> result; result.setScale(s); return result; }
	static matrix3x3<T> scale(T sx, T sy, T sz) { matrix3x3<T> result; result.setScale(sx, sy, sz); return result; }
	static matrix3x3<T> scale(const vector3<T>& s) { matrix3x3<T> result; result.setScale(s); return result; }
};

typedef matrix3x3<float> float3x3;
typedef matrix3x3<double> double3x3;
