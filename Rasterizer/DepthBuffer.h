#pragma once
#include <cstdlib>
#include <cstring>
#include <limits>


enum DepthTest {
	DEPTH_TEST_ALWAYS,
	DEPTH_TEST_LT,
	DEPTH_TEST_LTE,
	DEPTH_TEST_EQ,
	DEPTH_TEST_NE,
	DEPTH_TEST_GTE,
	DEPTH_TEST_GT,
};


class CDepthBuffer
{
private:
	int mWidth, mHeight;
	DepthTest mDepthTest;
	float* mvBuffer;
public:
	CDepthBuffer(int width, int height, DepthTest depthTest = DEPTH_TEST_ALWAYS);
	~CDepthBuffer();

	void clear(void);
	inline void setDepthTest(DepthTest depthTest) { mDepthTest = depthTest; }

	bool test(int x, int y, float value);
	inline void set(int x, int y, float value) { if (x >= 0 && x < mWidth && y >= 0 && y < mHeight) mvBuffer[y * mWidth + x] = value; }
};

