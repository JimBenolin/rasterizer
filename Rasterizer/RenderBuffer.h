#pragma once

#include "vector4.h"

class CRenderBuffer
{
private:
	int mWidth, mHeight, mSamples;
	ubyte4 mClearColor, mColor;
	ubyte4* mvBuffer;
private:
	inline size_t sampleAddress(int x, int y, int s) { return (y * mWidth + x) * mSamples + s; }
public:
	CRenderBuffer(int width, int height, int samples);
	~CRenderBuffer();

	void clear(void);
	inline void setClearColor(const ubyte4& color) { mClearColor = color; }

	inline ubyte4 get(int x, int y, int s) { return mvBuffer[sampleAddress(x, y, s)]; }
	inline void set(int x, int y, int s, ubyte4 color) { if (x >= 0 && x < mWidth && y >= 0 && y < mHeight && s >= 0 && s < mSamples) mvBuffer[sampleAddress(x, y, s)] = color; }
};

