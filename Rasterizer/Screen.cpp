#include "Screen.h"


CScreen::CScreen(std::string name, int width, int height)
	: mName(name), mWidth(width), mHeight(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "[SDL]  Could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		exit(-1);
	}
	else
	{
		//Create window
		mpWindow = SDL_CreateWindow(mName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
		if (mpWindow == NULL)
		{
			std::cout << "[SDL]  Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			exit(-1);
		}
		else
		{
			mpSurface = SDL_GetWindowSurface(mpWindow);
			mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED);
			if (mpRenderer == NULL)
			{
				std::cout << "[SDL]  Could not create Renderer! SDL_Error: " << SDL_GetError() << std::endl;
				exit(-1);
			}

			mpDepthBuffer = new CDepthBuffer(width, height);

			mColor = { 0x00, 0x00, 0x00, 0xff };
			mClearColor = { 0xff, 0xff, 0xff, 0x00 };
			clear();
		}
	}

}


CScreen::~CScreen()
{
	SDL_DestroyWindow(mpWindow);
	SDL_Quit();
}


ScreenAction CScreen::getUserInput(Movement& movement)
{
//	bool isEvent = (SDL_PollEvent(&mEvent.event) != 0);
//	if (isEvent) {
	while (SDL_PollEvent(&mEvent.event)) {

		SDL_Event event = mEvent.event;

		int x = event.motion.x;
		int y = event.motion.y;

//		if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
//		{
			mEvent.xOld = mEvent.x;
			mEvent.yOld = mEvent.y;
			mEvent.x = x;
			mEvent.y = y;
//		}
//		else
//		{
//			mEvent.mouseLeftDown = false;
//			mEvent.mouseRightDown = false;
//		}

		std::cout << "Event: pixel (" << mEvent.x << ", " << mEvent.y << ")" << std::endl;

		if (event.key.type == SDL_KEYDOWN && !keyDown)
		{
			keyDown = true;

			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE:
				return SCREEN_ACTION_QUIT;
				break;

			case SDLK_SPACE:
				isPaused = (isPaused ? false : true);
				singleStep = isPaused;
				break;

			case SDLK_u:
				update();
				break;

			case SDLK_f:
				isPaused = true;
				singleStep = true;
				update();
				break;

			case SDLK_KP_PLUS:
			case SDLK_PLUS:
			case SDLK_PAGEUP:
				break;

			case SDLK_KP_MINUS:
			case SDLK_MINUS:
			case SDLK_PAGEDOWN:
				break;

			case SDLK_w:
				movement.y -= 1;
				break;

			case SDLK_s:
				movement.y += 1;
				break;

			case SDLK_a:
				movement.x -= 1;
				break;

			case SDLK_d:
				movement.x += 1;
				break;

			case SDLK_q:
				movement.fov -= 0.1f;
				break;

			case SDLK_e:
				movement.fov += 0.1f;
				break;


			default:
				break;
			}

		}
		else if (event.key.type == SDL_KEYUP && keyDown) {
			keyDown = false;

		}
		else if (event.key.type == SDL_MOUSEMOTION && mEvent.mouseLeftDown) {
			std::cout << "Move: pixel (" << mEvent.x << ", " << mEvent.y << ")" << std::endl;

			drawLine(uint2(mEvent.xOld, mEvent.yOld), uint2(mEvent.x, mEvent.y));
			update();

		}
		else if (event.key.type == SDL_MOUSEBUTTONDOWN) {
			std::cout << "Click: pixel (" << mEvent.x << ", " << mEvent.x << ")" << std::endl;

			mEvent.mouseLeftDown = (event.button.button == 1);
			mEvent.mouseRightDown = (event.button.button == 3);
			drawLine(uint2(mEvent.xOld, mEvent.yOld), uint2(mEvent.x, mEvent.y));
			update();
		}
		else if (event.key.type == SDL_MOUSEBUTTONUP) {
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


void CScreen::rasterize(const floattc& tc)
{
	float4 c[3] = { tc.vc0.c, tc.vc1.c, tc.vc2.c };

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

	bool t;
	float ev, A, B;
	float3 barycentric;

	float ev0 = e0.dot(float3(0.5f, 0.5f, 1));
	float ev1 = e1.dot(float3(0.5f, 0.5f, 1));
	float ev2 = e2.dot(float3(0.5f, 0.5f, 1));


	floatbb bb(floatt(tc.vc0.v, tc.vc1.v, tc.vc2.v));

	for (int y = int(bb.y0); y < int(bb.y1) + 1; y++)
	{
		for (int x = int(bb.x0); x < int(bb.x1) + 1; x++)
		{
			A = e0.x;
			B = e0.y;
			t = (A != 0 ? A > 0 : B > 0);
			ev = ev0 + A * x + B * y;
			if (!(ev > 0 || (ev == 0 && t)))
				continue;
			barycentric.u = ev / doubleArea;

			A = e1.x;
			B = e1.y;
			t = (A != 0 ? A > 0 : B > 0);
			ev = ev1 + A * x + B * y;
			if (!(ev > 0 || (ev == 0 && t)))
				continue;
			barycentric.v = ev / doubleArea;

			A = e2.x;
			B = e2.y;
			t = (A != 0 ? A > 0 : B > 0);
			ev = ev2 + A * x + B * y;
			if (!(ev > 0 || (ev == 0 && t)))
				continue;
			barycentric.w = 1 - barycentric.u - barycentric.v;

			float z = float3(tc.vc0.v.z, tc.vc1.v.z, tc.vc2.v.z).dot(barycentric);
			if (mpDepthBuffer->test(x, y, z))
			{
				setColor(barycentric.v * c[0] + barycentric.w * c[1] + barycentric.u * c[2]);
				drawPixel(uint2(x, y));
				mpDepthBuffer->set(x, y, z);
			}
		}
	}
}
