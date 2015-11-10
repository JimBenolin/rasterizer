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
	int mWidth, mHeight, mSamples;
	DepthTest mDepthTest;
	float* mvBuffer;
private:
	inline size_t sampleAddress(int x, int y, int s) { return (y * mWidth + x) * mSamples + s; }
public:
	CDepthBuffer(int width, int height, int samples, DepthTest depthTest = DEPTH_TEST_GTE);
	~CDepthBuffer();

	void clear(void);
	inline void setDepthTest(DepthTest depthTest) { mDepthTest = depthTest; }

	bool test(int x, int y, int s, float value);
	inline void set(int x, int y, int s, float value) { if (x >= 0 && x < mWidth && y >= 0 && y < mHeight) mvBuffer[sampleAddress(x, y, s)] = value; }
};

