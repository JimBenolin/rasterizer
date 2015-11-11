#include "DepthBuffer.h"


CDepthBuffer::CDepthBuffer(int width, int height, int samples, DepthTest depthTest)
	: mWidth(width), mHeight(height), mSamples(samples), mDepthTest(depthTest)
{
	mvBuffer = (float*)calloc(mWidth * mHeight * mSamples, sizeof(float));
}


CDepthBuffer::~CDepthBuffer()
{
}


void CDepthBuffer::clear(void)
{
	float value = 0.0f;
	switch (mDepthTest)
	{
	case DEPTH_TEST_LT:
	case DEPTH_TEST_LTE:
		value = std::numeric_limits<float>::infinity();
		break;
	case DEPTH_TEST_EQ:
		break;
	case DEPTH_TEST_NE:
		break;
	case DEPTH_TEST_GTE:
	case DEPTH_TEST_GT:
	default:
		value = -std::numeric_limits<float>::infinity();
		break;
	}
	std::fill(mvBuffer, mvBuffer + mWidth * mHeight * mSamples, value);
	//memset(mvBuffer, int(value), mWidth * mHeight * mSamples * sizeof(float));
}


bool CDepthBuffer::test(int x, int y, int s, float value)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return false;
		
	bool result = false;
	float currentValue = mvBuffer[sampleAddress(x, y, s)];
	
	switch (mDepthTest)
	{
	case DEPTH_TEST_ALWAYS:
		result = true;
		break;
	case DEPTH_TEST_LT:
		result = value < currentValue;
		break;
	case DEPTH_TEST_LTE:
		result = value <= currentValue;
		break;
	case DEPTH_TEST_EQ:
		result = value == currentValue;
		break;
	case DEPTH_TEST_NE:
		result = value != currentValue;
		break;
	case DEPTH_TEST_GTE:
		result = value >= currentValue;
		break;
	case DEPTH_TEST_GT:
	default:
		result = value > currentValue;
		break;
	}

	return result;
}