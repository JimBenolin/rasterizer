#include "DepthBuffer.h"


CDepthBuffer::CDepthBuffer(int width, int height, DepthTest depthTest)
	: mWidth(width), mHeight(height), mDepthTest(depthTest)
{
	mvBuffer = (float*)calloc(width * height, sizeof(float));
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
		break;
	case DEPTH_TEST_LTE:
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
	memset(mvBuffer, int(value), mWidth * mHeight * sizeof(float));
}


bool CDepthBuffer::test(int x, int y, float value)
{
	if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		return false;
		
	bool result = false;
	float currentValue = mvBuffer[y * mWidth + x];
	
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