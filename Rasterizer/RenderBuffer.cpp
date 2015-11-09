#include "RenderBuffer.h"


CRenderBuffer::CRenderBuffer(int width, int height, int samples)
	: mWidth(width), mHeight(height), mSamples(samples)
{
	mvBuffer = (ubyte4*)calloc(mWidth * mHeight * mSamples, sizeof(ubyte4));
}


CRenderBuffer::~CRenderBuffer()
{
}


void CRenderBuffer::clear(void)
{
	for (size_t sampleId = 0; sampleId < mWidth * mHeight * mSamples; sampleId++)
		mvBuffer[sampleId] = mClearColor;
}
