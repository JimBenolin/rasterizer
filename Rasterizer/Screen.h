#pragma once

#include <iostream>

#include "Rasterizer.h"
#include "SDL.h"
#include "JimMath.h"
#include "DepthBuffer.h"
#include "RenderBuffer.h"
#include "BoundingBox.h"


enum ScreenAction {
	SCREEN_ACTION_NONE,
	SCREEN_ACTION_QUIT,
};

struct ScreenEvent {
	SDL_Event event;
	int x, y, xOld, yOld;
	bool mouseLeftDown;
	bool mouseRightDown;
};

const static float sampleDelta = 1.0f / 16.0f;
static float2 SamplePositions1[] {
	{ 8 * sampleDelta, 8 * sampleDelta },
};

static float2 SamplePositions4[] {
	{ 6 * sampleDelta, 14 * sampleDelta },
	{ 2 * sampleDelta, 6 * sampleDelta },
	{ 10 * sampleDelta, 2 * sampleDelta },
	{ 14 * sampleDelta, 10 * sampleDelta },
};


static float2 SamplePositions8[] {
	{ 15 * sampleDelta, 15 * sampleDelta },
	{ 5 * sampleDelta, 13 * sampleDelta },
	{ 9 * sampleDelta, 11 * sampleDelta },
	{ 1 * sampleDelta, 9 * sampleDelta },
	{ 13 * sampleDelta, 7 * sampleDelta },
	{ 7 * sampleDelta, 5 * sampleDelta },
	{ 3 * sampleDelta, 3 * sampleDelta },
	{ 11 * sampleDelta, 1 * sampleDelta },
};


static float2 SamplePositions16[] {
	{ 1 * sampleDelta, 0 * sampleDelta },
	{ 8 * sampleDelta, 1 * sampleDelta },
	{ 4 * sampleDelta, 2 * sampleDelta },
	{ 11 * sampleDelta, 3 * sampleDelta },
	{ 15 * sampleDelta, 4 * sampleDelta },
	{ 7 * sampleDelta, 5 * sampleDelta },
	{ 3 * sampleDelta, 6 * sampleDelta },
	{ 12 * sampleDelta, 7 * sampleDelta },
	{ 0 * sampleDelta, 8 * sampleDelta },
	{ 9 * sampleDelta, 9 * sampleDelta },
	{ 5 * sampleDelta, 10 * sampleDelta },
	{ 13 * sampleDelta, 11 * sampleDelta },
	{ 2 * sampleDelta, 12 * sampleDelta },
	{ 10 * sampleDelta, 13 * sampleDelta },
	{ 6 * sampleDelta, 14 * sampleDelta },
	{ 14 * sampleDelta, 15 * sampleDelta },
};


class CScreen
{
private:
	SDL_Window* mpWindow;
	SDL_Surface* mpSurface;
	SDL_Renderer* mpRenderer;
	std::string mName;
	int mWidth, mHeight, mSamples;
	ubyte4 mClearColor, mColor;
	CDepthBuffer* mpDepthBuffer;
	CRenderBuffer* mpRenderBuffer;
	float2* mSamplePositions;

	ScreenEvent mEvent;
	bool isPaused;
	bool singleStep;
	bool keyDown;

private:
	inline void setRenderDrawColor(const ubyte4& color) { SDL_SetRenderDrawColor(mpRenderer, mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a); }
public:
	CScreen(std::string name, int width, int height, int samples = 1);
	~CScreen();

	inline int getWidth(void) const { return mWidth; }
	inline int getHeight(void) const { return mHeight; }
	inline void setColor(const ubyte4& color) { mColor = color; mColor.clamp(0, 255); }
	inline void setColor(const float4& color) { setColor(ubyte4(uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255), uint8_t(color.a * 255))); }
	inline void setClearColor(const ubyte4& color) { mClearColor = color; if (mSamples > 1) mpRenderBuffer->setClearColor(color); }
	inline void clear(void) { setRenderDrawColor(mClearColor); SDL_RenderClear(mpRenderer); if (mSamples > 1) mpRenderBuffer->clear(); mpDepthBuffer->clear(); }
	inline void update(void) { if (mSamples > 1) resolve(); SDL_RenderPresent(mpRenderer); }

	ScreenAction getUserInput(Movement& movement);

	void drawPixel(const uint16_t x, const uint16_t y);
	void drawPixel(const uint2& p);
	void drawLine(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1);
	void drawLine(const uint2& p0, const uint2& p1);
	void drawLine(const float2& p0, const float2& p1);

	void rasterize(const floattc& tc);
	void resolve(void);
};

