#include "Screen.h"


CScreen::CScreen(std::string name, int width, int height, int samples)
	: mName(name), mWidth(width), mHeight(height), mSamples(samples)
{
	bFullscreen = false;
	init();
}


CScreen::CScreen(std::string name, int samples)
	: mName(name), mSamples(samples)
{
	bFullscreen = true;
	init();
}


void CScreen::init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "[SDL]  Could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	SDL_GetDisplayBounds(0, &mScreenBounds);

	if (bFullscreen)
	{
		mWidth = mScreenBounds.w;
		mHeight = mScreenBounds.h;
		mpWindow = SDL_CreateWindow(mName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		mpWindow = SDL_CreateWindow(mName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
	}

	if (mpWindow == NULL)
	{
		std::cout << "[SDL]  Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	mpSurface = SDL_GetWindowSurface(mpWindow);
	mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED);

	if (mpRenderer == NULL)
	{
		std::cout << "[SDL]  Could not create Renderer! SDL_Error: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	mpDepthBuffer = new CDepthBuffer(mWidth, mHeight, mSamples);

	if (mSamples == 1)
		mSamplePositions = SamplePositions1;
	else if (mSamples == 4)
		mSamplePositions = SamplePositions4;
	else if (mSamples == 8)
		mSamplePositions = SamplePositions8;
	else if (mSamples == 16)
		mSamplePositions = SamplePositions16;

	mpRenderBuffer = new CRenderBuffer(mWidth, mHeight, mSamples);

	mColor = { 0x00, 0x00, 0x00, 0xff };
	mClearColor = { 0xff, 0xff, 0xff, 0x00 };
	clear();

	bKeyDown = false;
	bPaused = false;
	bWireframe = false;
	bDepthColor = false;
}


CScreen::~CScreen()
{
	SDL_SetWindowFullscreen(mpWindow, NULL);
	SDL_DestroyWindow(mpWindow);
	SDL_Quit();
}


const static float movementVelocity = 5.0f;

ScreenAction CScreen::getUserInput(Movement& movement)
{
	while (SDL_PollEvent(&mEvent.event))
	{
		SDL_Event event = mEvent.event;

		int x = event.motion.x;
		int y = event.motion.y;

		mEvent.x = x;
		mEvent.y = y;
		movement.x = event.motion.x;
		movement.y = event.motion.y;

		std::cout << "(" << mEvent.x << ", " << mEvent.y << ")" << std::endl;

		if (event.key.type == SDL_KEYDOWN || event.key.type == SDL_KEYUP)
		{
			bKeyDown = true;

			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE:
				return SCREEN_ACTION_QUIT;
				break;

			case SDLK_u:
				update();
				break;

//			case SDLK_f:
//				isPaused = true;
//				singleStep = true;
//				update();
//				break;

			case SDLK_KP_PLUS:
			case SDLK_PLUS:
			case SDLK_PAGEUP:
				break;

			case SDLK_KP_MINUS:
			case SDLK_MINUS:
			case SDLK_PAGEDOWN:
				break;

			case SDLK_w:
				movement.yVelocity = -movementVelocity;
				break;

			case SDLK_s:
				movement.yVelocity = movementVelocity;
				break;

			case SDLK_a:
				movement.xVelocity = -movementVelocity;
				break;

			case SDLK_d:
				movement.xVelocity = movementVelocity;
				break;

			case SDLK_q:
				movement.fov -= 0.01f;
				break;

			case SDLK_e:
				movement.fov += 0.01f;
				break;

			default:
				break;
			}

		}
		
		if (event.key.type == SDL_KEYUP)
		{
			bKeyDown = false;

			switch (event.key.keysym.sym) {

			case SDLK_w:
			case SDLK_s:
				movement.yVelocity = 0;
				break;

			case SDLK_a:
			case SDLK_d:
				movement.xVelocity = 0;
				break;

			case SDLK_f:
				bWireframe = !bWireframe;
				break;

			case SDLK_SPACE:
				bPaused = (bPaused ? false : true);
				break;

			case SDLK_z:
				bDepthColor = (bDepthColor ? false : true);
				break;

			default:
				break;
			}
		}

//		if (event.key.type == SDL_MOUSEMOTION && mEvent.mouseLeftDown)
		if (event.key.type == SDL_MOUSEMOTION)
		{

			movement.pitch = (mHeight / 2 - mEvent.y) * 0.005f;
			movement.pitch = std::min(float(M_PI), std::max(-float(M_PI), movement.pitch));

			movement.yaw = (mWidth / 2 - mEvent.x) * 0.005f;
//			movement.yaw = std::min(float(M_PI), std::max(-float(M_PI), movement.yaw));
		}
		else if (event.key.type == SDL_MOUSEBUTTONDOWN)
		{
			std::cout << "Click: pixel (" << mEvent.x << ", " << mEvent.x << ")" << std::endl;

			mEvent.mouseLeftDown = (event.button.button == 1);
			mEvent.mouseRightDown = (event.button.button == 3);
//			drawLine(uint2(mEvent.xOld, mEvent.yOld), uint2(mEvent.x, mEvent.y));
//			update();
		}
		else if (event.key.type == SDL_MOUSEBUTTONUP)
		{
			mEvent.mouseLeftDown = !(event.button.button == 1);
			mEvent.mouseRightDown = !(event.button.button == 3);
		}

	}

	return SCREEN_ACTION_NONE;
}


void CScreen::drawPixel(const uint16_t x, const uint16_t y)
{
	SDL_SetRenderDrawColor(mpRenderer, mColor.r, mColor.g, mColor.b, mColor.a);
	SDL_RenderDrawPoint(mpRenderer, x, y);
}


void CScreen::drawPixel(const uint2& p)
{
	drawPixel(p.x, p.y);
}


void CScreen::drawLine(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1)
{
	SDL_SetRenderDrawColor(mpRenderer, mColor.r, mColor.g, mColor.b, mColor.a);
	SDL_RenderDrawLine(mpRenderer, x0, y0, x1, y1);
}


void CScreen::drawLine(const uint2& p0, const uint2& p1)
{
	drawLine(p0.x, p0.y, p1.x, p1.y);
}


void CScreen::drawLine(const float2& p0, const float2& p1)
{
	drawLine(uint16_t(p0.x + 0.5f), uint16_t(p0.y + 0.5f), uint16_t(p1.x + 0.5f), uint16_t(p1.y + 0.5f));
}


void CScreen::drawTexture(const CTexture& texture, const int x, const int y, const int width, const int height)
{
	int scaleWidth = (width == -1 ? texture.getWidth() : width);
	int scaleHeight = (height == -1 ? texture.getHeight() : height);

	float dx = 1 / float(scaleWidth - 1);
	float dy = 1 / float(scaleHeight - 1);

	for (int yy = 0; yy < scaleHeight; yy++)
	{
		for (int xx = 0; xx < scaleWidth; xx++)
		{
			setColor(texture.getTexel(xx * dx, yy * dy));
			drawPixel(x + xx, y + yy);
		}
	}
}



void CScreen::rasterize(const floattc& tc)
{
	float doubleArea;
	float3 e0, e1, e2;

	tc.setup(e0, e1, e2, doubleArea);

	if (false && doubleArea <= 0)
	{
		//  triangle is back-facing or zero-area
		float3 v[3] = { tc.vc0.v, tc.vc1.v, tc.vc2.v };
		setColor(ubyte4(0, 255, 0, 0));
		drawLine(uint16_t(v[0].x), uint16_t(v[0].y), uint16_t(v[1].x), uint16_t(v[1].y));
		drawLine(uint16_t(v[1].x), uint16_t(v[1].y), uint16_t(v[2].x), uint16_t(v[2].y));
		drawLine(uint16_t(v[2].x), uint16_t(v[2].y), uint16_t(v[0].x), uint16_t(v[0].y));
		return;
	}

	if (bWireframe)
	{
		//  triangle is back-facing or zero-area
		float3 v[3] = { tc.vc0.v, tc.vc1.v, tc.vc2.v };
		if (v[0].x < 0 || v[0].x >= mWidth)
			return;
		if (v[1].x < 0 || v[1].x >= mWidth)
			return;
		if (v[2].x < 0 || v[2].x >= mWidth)
			return;
		if (v[0].y < 0 || v[0].y >= mHeight)
			return;
		if (v[1].y < 0 || v[1].y >= mHeight)
			return;
		if (v[2].y < 0 || v[2].y >= mHeight)
			return;
		setColor(ubyte4(0, 0, 0, 0));
		drawLine(uint16_t(v[0].x), uint16_t(v[0].y), uint16_t(v[1].x), uint16_t(v[1].y));
		drawLine(uint16_t(v[1].x), uint16_t(v[1].y), uint16_t(v[2].x), uint16_t(v[2].y));
		drawLine(uint16_t(v[2].x), uint16_t(v[2].y), uint16_t(v[0].x), uint16_t(v[0].y));
		return;
	}

	bool t;
	float ev, A, B;
	float3 barycentric;
	uint2 p;

	for (int s = 0; s < mSamples; s++)
	{

		float ev0 = e0.dot(float3(mSamplePositions[s].x, mSamplePositions[s].y, 1));
		float ev1 = e1.dot(float3(mSamplePositions[s].x, mSamplePositions[s].y, 1));
		float ev2 = e2.dot(float3(mSamplePositions[s].x, mSamplePositions[s].y, 1));

		floatbb bb(floatt(tc.vc0.v, tc.vc1.v, tc.vc2.v));
		bb.clamp(0, float(mWidth), 0, float(mHeight));

		for (p.y = int(bb.y0); p.y < int(bb.y1) + 1; p.y++)
		{
			for (p.x = int(bb.x0); p.x < int(bb.x1) + 1; p.x++)
			{
				A = e0.x;
				B = e0.y;
				t = (A != 0 ? A > 0 : B > 0);
				ev = ev0 + A * p.x + B * p.y;
				if (!(ev > 0 || (ev == 0 && t)))
					continue;
				barycentric.w = ev / doubleArea;

				A = e1.x;
				B = e1.y;
				t = (A != 0 ? A > 0 : B > 0);
				ev = ev1 + A * p.x + B * p.y;
				if (!(ev > 0 || (ev == 0 && t)))
					continue;
				barycentric.u = ev / doubleArea;

				A = e2.x;
				B = e2.y;
				t = (A != 0 ? A > 0 : B > 0);
				ev = ev2 + A * p.x + B * p.y;
				if (!(ev > 0 || (ev == 0 && t)))
					continue;
				barycentric.v = 1 - barycentric.u - barycentric.w;

				float z = float3(tc.vc0.v.z, tc.vc1.v.z, tc.vc2.v.z).dot(barycentric);
				if (z < -1 || z > 1)
					continue;
				jmath::clamp<float>(z, -1, 1);
				if (mpDepthBuffer->test(p.x, p.y, s, z))
				{
					if (bDepthColor)
						shadeDepth(p, z);
					else
						shade(tc, p, barycentric, s);

					mpDepthBuffer->set(p.x, p.y, s, z);
				}
			}
		}
	}

}


void CScreen::shade(const floattc& triangle, const uint2& pixel, const float3& barycentric, const int sample)
{
	setColor(barycentric.u * triangle.vc0.c + barycentric.v * triangle.vc1.c + barycentric.w * triangle.vc2.c);

	if (mSamples > 1)
		mpRenderBuffer->set(pixel.x, pixel.y, sample, mColor);
	else
		drawPixel(uint2(pixel.x, pixel.y));
}


void CScreen::shadeDepth(const uint2& pixel, const float z)
{
	if (z < -1)
		setColor(float4(1, 0, 0, 0));
	else if (z > 1)
		setColor(float4(0, 1, 0, 0));
	else
	{
		float zColor = std::pow((z + 1) / 2, 50);
		setColor(float4(zColor, zColor, zColor, zColor));
	}

	if (mSamples > 1)
		mpRenderBuffer->set(pixel.x, pixel.y, 0, mColor);
	else
		drawPixel(uint2(pixel.x, pixel.y));
}


void CScreen::resolve(void)
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			ubyte4 color = { 0, 0, 0, 0 };
			uint4 totalColor = { 0, 0, 0, 0 };
			for (int s = 0; s < mSamples; s++)
			{
				color = mpRenderBuffer->get(x, y, s);
				totalColor += uint4(color.r, color.g, color.b, color.a);
			}
			setColor(ubyte4(uint8_t(totalColor.r / mSamples), uint8_t(totalColor.g / mSamples), uint8_t(totalColor.b / mSamples), uint8_t(totalColor.a / mSamples)));
			drawPixel(uint2(x, y));
		}
	}
}
