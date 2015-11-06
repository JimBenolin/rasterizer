#pragma once

#include <iostream>

#include "Rasterizer.h"
#include "SDL.h"
#include "JimMath.h"
#include "DepthBuffer.h"
#include "BoundingBox.h"


enum ScreenAction {
	SCREEN_ACTION_NONE,
	SCREEN_ACTION_QUIT,
	SCREEN_ACTION_STATISTICS,
	SCREEN_ACTION_WRITE_BMP
};

struct ScreenEvent {
	SDL_Event event;
	int x, y, xOld, yOld;
	bool mouseLeftDown;
	bool mouseRightDown;
};

class CScreen
{
private:
	SDL_Window* mpWindow;
	SDL_Surface* mpSurface;
	SDL_Renderer* mpRenderer;
	std::string mName;
	int mWidth, mHeight;
	ubyte4 mClearColor, mColor;
	CDepthBuffer* mpDepthBuffer;

	ScreenEvent mEvent;
	bool isPaused;
	bool singleStep;
	bool keyDown;

private:
	inline void setRenderDrawColor(const ubyte4& color) { SDL_SetRenderDrawColor(mpRenderer, mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a); }
public:
	CScreen(std::string name, int width, int height);
	~CScreen();

	inline int getWidth(void) const { return mWidth; }
	inline int getHeight(void) const { return mHeight; }
	inline void setColor(const ubyte4& color) { mColor = color; mColor.clamp(0, 255); }
	inline void setColor(const float4& color) { setColor(ubyte4(uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255), uint8_t(color.a * 255))); }
	inline void setClearColor(const ubyte4& color) { mClearColor = color; }
	inline void clear(void) { setRenderDrawColor(mClearColor); SDL_RenderClear(mpRenderer); mpDepthBuffer->clear(); }
	inline void update(void) { SDL_RenderPresent(mpRenderer); }

	ScreenAction getUserInput(Movement& movement);

	void drawPixel(const uint16_t x, const uint16_t y);
	void drawPixel(const uint2& p);
	void drawLine(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1);
	void drawLine(const uint2& p0, const uint2& p1);
	void drawLine(const float2& p0, const float2& p1);

//	void draw(const floatt& t);
//	void draw(const floattc& tc);
//	void draw(const floattn& tn);
	void rasterize(const floattc& tc);
};

