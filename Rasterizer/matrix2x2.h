#pragma once

#include "vector2.h"

template<typename T> class matrix2x2
{
	union
	{
		struct
		{
			T _11, _12;
			T _21, _22;
		};
		struct{
			vector2<T> m[2];
		};
		T mData[2][2];
	};

public:
	//  Constructors
	matrix2x2<T>() {}
	matrix2x2<T>(const vector2<T>& v0, const vector2<T>& v1, bool columnVectors = false) { if (columnVectors) { setColumns(v0, v1); } else { setRows(v0, v1); } }
	matrix2x2<T>(T _11, T _12, T _21, T _22) : _11(_11), _12(_12), _21(_21), _22(_22) {}
	explicit matrix2x2<T>(const float* elements) { assert(elements); memcpy(mData, elements, sizeof(mData)); }

	//  element access
	vector2<T> operator[](int row) const { assert(0 <= row && row < 2); return m[row]; }
	vector2<T>& operator[](int row) { assert(0 <= row && row < 2); return m[row]; }
	T& get(int row, int col) { assert(0 <= row && row < 2); assert(0 <= col && col < 2); return m[row][col]; }
	const T& get(int row, int col) const { assert(0 <= row && row < 2); assert(0 <= col && col < 2); return m[row][col]; }
	operator T*() { return mData; };
	operator const T*() const { return mData; };

	//  row/column access
	vector2<T> getRow(int row) const { assert(row >= 0 && row < 2); return m[row]; }
	vector2<T> getColumn(int col) const { assert(col >= 0 && col < 2); return vector2<T>(m[0][col], m[1][col]); }
	void setRow(int row, const vector2<T>& v) { assert(row >= 0 && row < 2); m[row] = v; }
	void setRows(const vector2<T>& v0, const vector2<T>& v1) { setRow(0, v0); setRow(1, v1); }
	void setColumn(int col, const vector2<T>& v) { assert(col >= 0 && col < 2); m[0][col] = v.x; m[1][col] = v.y; }
	void setColumns(const vector2<T>& v0, const vector2<T>& v1) { setColumn(0, v0); setColumn(1, v1); }

	//  setup matrix
	void setZero(void) { memset(mData, 0, sizeof(mData)); }
	void setIdentity() { setZero(); m[0][0] = m[1][1] = T(1); }
	void setScale(T s) { setZero(); m[0][0] = m[1][1] = s; }
	void setScale(T sx, T sy) { setZero(); m[0][0] = sx; m[1][1] = sy; }
	void setScale(const vector2<T>& s) { setScale(s.x, s.y); }
	void setRotate(T a) { T sinA = sin(a), cosA = cos(a); m[0] = vector2<T>(cosA, -sinA); m[1] = vector2<T>(sinA, cosA); }

	//  standard matrix operations
	void transpose(void) { setColumns(getRow(0), getRow(1)); }
	void transpose(matrix2x2<T>& result) const { result = *this; result.transpose(); }
	matrix2x2<T> transposed(void) const { matrix2x2<T> result(*this); result.transpose(); return result; }
	void invert(void) { T det = determinant(); *this = matrix2x2<T>(m[1][1], -m[1][0], -m[0][1], m[0][0]) / det; }
	void invert(matrix2x2<T>& result) const { result = *this; result.invert(); }
	matrix2x2<T> inverted(void) const { matrix2x2<T> result(*this); result.invert(); return result; }
	T determinant(void) const { return m[0][0] * m[1][1] - m[0][1] * m[1][0]; }

	//  arithmetic operations
	matrix2x2<T> operator+(const matrix2x2<T>& rhs) const { return matrix2x2<T>(m[0] + rhs[0], m[1] + rhs[1]); }
	matrix2x2<T> operator-(const matrix2x2<T>& rhs) const { return matrix2x2<T>(m[0] - rhs[0], m[1] - rhs[1]); }
	matrix2x2<T> operator*(const matrix2x2<T>& rhs) const { matrix2x2<T> M; for (int row = 0; row < 2; row++) for (int col = 0; col < 2; col++) M[row][col] = dot(getRow(row), rhs.getColumn(col)); return M; }
	matrix2x2<T>& operator+=(const matrix2x2<T>& rhs) { return *this = *this + rhs; }
	matrix2x2<T>& operator-=(const matrix2x2<T>& rhs) { return *this = *this - rhs; }
	matrix2x2<T>& operator*=(const matrix2x2<T>& rhs) { return *this = *this * rhs; }
	matrix2x2<T> operator+(const T v) const { return matrix2x2<T>(m[0] + v, m[1] + v); }
	matrix2x2<T> operator-(const T v) const { return matrix2x2<T>(m[0] - v, m[1] - v); }
	matrix2x2<T> operator*(const T v) const { return matrix2x2<T>(m[0] * v, m[1] * v); }
	matrix2x2<T> operator/(const T v) const { return *this * (T(1) / v); }
	matrix2x2<T>& operator+=(const T v) { return *this = *this + v; }
	matrix2x2<T>& operator-=(const T v) { return *this = *this - v; }
	matrix2x2<T>& operator*=(const T v) { return *this = *this * v; }
	matrix2x2<T>& operator/=(const T v) { return *this = *this / v; }
	friend matrix2x2<T> operator+(const T v, const matrix2x2<T>& rhs) { return rhs + v; }
	friend matrix2x2<T> operator*(const T v, const matrix2x2<T>& rhs) { return rhs * v; }

	//  transforms
	vector2<T> operator*(const vector2<T>& v) const { return vector2<T>(getColumn(0).dot(v), getColumn(1).dot(v)); }
	vector2<T> transform(const vector2<T>& v) const { return *this * v; }
	void transform(const vector2<T>& v, vector2<T>& dst) const { dst = transform(v); }
	friend vector2<T> operator*(const vector2<T> &v, const matrix2x2<T>& M) { M.transform(v); }

	//  debug
	friend std::ostream& operator<<(std::ostream& os, const matrix2x2<T>& m) { os << "[ " << m[0] << ", " << m[1] << " ]"; return os; }
	friend std::istream& operator>>(std::istream& is, matrix2x2<T>& m) { is >> m[0] >> m[1]; return is; }

	//  statics
	static matrix2x2<T> zero(void) { matrix2x2<T> result; result.setZero(); return result; }
	static matrix2x2<T> identity(void) { matrix2x2<T> result; result.setIdentity(); return result; }
	static matrix2x2<T> scale(T s) { matrix2x2<T> result; result.setScale(s); return result; }
	static matrix2x2<T> scale(T sx, T sy) { matrix2x2<T> result; result.setScale(sx, sy); return result; }
	static matrix2x2<T> scale(const vector2<T>& s) { matrix2x2<T> result; result.setScale(s); return result; }
};

typedef matrix2x2<float> float2x2;
typedef matrix2x2<double> double2x2;
