#include <vector>
#include <chrono>
#include <cmath>

#include "color.h"
#include "triangle.h"
#include "JimMath.h"
#include "Screen.h"
#include "Model.h"
#include "Timer.h"


int windowWidth = 500;
int windowHeight = 500;

static float rotationVelocity = float((2 * M_PI) / 40);
static float rotationAngle = 0.0f;

int main(int argc, char* argv[])
{
	CScreen screen("Test", windowWidth, windowHeight, 1);
//	CScreen screen("Test");

	int width = screen.getWidth();
	int height = screen.getHeight();

	float4x4 screenScaleT = float4x4::scale(float(width), float(height), 1.0f);
	float4x4 screenTranslationT = float4x4::translation(float(width) / 2, float(height) / 2, 0);
	float4x4 screenTransformT = screenTranslationT * screenScaleT;

	screen.setClearColor(ubyte4(230, 230, 255, 255));
	screen.clear();

	float4x4 modelT, viewT, projectionT;
	float4x4 mvpT;

	float2 position(0, 10);
	Movement movement = { 0, 0, 0, 0, float(M_PI / 2) };

	CModel model;
	model.addAxes();
	model.addCubeRGB(float3(0, 0, 0), float3(1, 1, 1));
	model.addCubeRGB(float3(0.7f, 0.7f, 0.7f), float3(0.4f, 0.4f, 0.4f));
	CModel checkerBoard;
	checkerBoard.addCheckerBoard(10);

	CTimer timer;
	while (screen.getUserInput(movement) != SCREEN_ACTION_QUIT)
	{
		screen.clear();

		viewT = float4x4::cameraFirstPersonRH(float3(position.x, float(M_PI / 3), position.y), movement.pitch, movement.yaw);
//		viewT = float4x4::cameraLookAtRH(float3(position.x, 3.14159f * 0.5f, position.y), float3(0, 0, 0), float3(0, 1, 0));
		projectionT = float4x4::projectionPerspective(movement.fov, float(width), float(height), -0.01f, -50.0f);
//		projectionT = float4x4::projectionPerspectiveB(0.1f, 1000, 5, -5, -5, 5);

#if 1
		modelT = float4x4::translation(0, 1, 0) * float4x4::rotateAxisY(-rotationAngle);
		mvpT = projectionT * viewT * modelT;
		for (auto triangle : model.getTriangles())
		{
			floattc triangleT = triangle;
			triangleT.transform(mvpT);
			
			if (triangleT.clip())
				continue;

			triangleT.transform(screenTransformT);

			screen.rasterize(triangleT);
		}

		modelT = float4x4::rotateAxisY(rotationAngle);
//		modelT = float4x4::translation(0, 0, -4);
		mvpT = projectionT * viewT * modelT;
		for (auto triangle : checkerBoard.getTriangles())
		{
			floattc triangleT = triangle;
			triangleT.transform(mvpT);

			if (triangleT.clip())
				continue;

			triangleT.transform(screenTransformT);

			screen.rasterize(triangleT);
		}
#endif

		screen.update();

		float frameTime = float(timer.getAndSet()) / 1000000.0f;

		if (!screen.isPaused())
		{
			rotationAngle += frameTime * rotationVelocity;
		}
		
		float2x2 rot = float2x2::rotation(movement.yaw);
		position += float2(movement.xVelocity, movement.yVelocity) * rot * frameTime;

//		std::cout << "frame time [s]: " << frameTime << std::endl;
	}

	return 0;
}