#include "triangle.h"
#include "JimMath.h"
#include "Screen.h"


int width = 500;
int height = 500;

const floatt model[] = {
		{ { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 } },
		{ { 1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } },

		{ { -1, -1, 1 }, { -1, 1, 1 }, { 1, 1, 1 } },
		{ { 1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 } },

		{ { -1, -1, -1 }, { -1, -1, 1 }, { 1, -1, 1 } },
		{ { 1, -1, 1 }, { 1, -1, -1 }, { -1, -1, -1 } },

		{ { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 } },
		{ { 1, 1, 1 }, { 1, 1, -1 }, { -1, 1, -1 } },

		{ { -1, -1, -1 }, { -1, 1, -1 }, { -1, 1, -1 } },
		{ { -1, 1, 1 }, { -1, -1, 1 }, { -1, -1, -1 } },

		{ { 1, -1, -1 }, { 1, 1, -1 }, { 1, 1, 1 } },
		{ { 1, 1, 1 }, { 1, -1, 1 }, { 1, -1, -1 } },
};

const floattn plane[] = {
		{
			{ { -5, 0, -5 }, { 0, 0, 0 } },
			{ { -5, 0, 5 }, { 0, 0, 0 } },
			{ { 5, 0, 5 }, { 0, 0, 0 } },
		},
		{
			{ { 5, 0, 5 }, { 0, 0, 0 } },
			{ { 5, 0, -5 }, { 0, 0, 0 } },
			{ { -5, 0, -5 }, { 0, 0, 0 } },
		},
};

float4 gray75 = { 0.75f, 0.75f, 0.75f, 0 };
float4 gray50 = { 0.5f, 0.5f, 0.5f, 0 };
float4 black = { 0, 0, 0, 0 };


floattc twoTriangleModel[] = {
		{
			{ { 1.1f, 0.1f, 0.0f }, gray75 },  //  x
			{ { 1.1f, -0.1f, 0.0f }, gray75 },
			{ { 2.0f, 0.0f, 0.0f }, gray75 },
		},
		{
			{ { -0.1f, 1.1f, 0.0f }, gray50 },  //  y
			{ { 0.1f, 1.1f, 0.0f }, gray50 },
			{ { 0.0f, 2.0f, 0.0f }, gray50 },
		},
		{
			{ { 0.1f, 0.0f, 1.1f }, black },  //  z
			{ { -0.1f, 0.0f, 1.1f }, black },
			{ { 0.0f, 0.0f, 2.0f }, black },
		},
		{
			{ { 1.0f, -1.0f, 0.0f }, { 1, 0, 0, 0 } },
			{ { 1.0f, 1.0f, 0.0f }, { 0, 1, 0, 0 } },
			{ { -1.0f, -1.0f, 0.0f }, { 0, 0, 1, 0 } },
		},
		{
			{ { -1.0f, 1.0f, 0.0f }, { 1, 0, 1, 0 } },
			{ { -1.0f, -1.0f, 0.0f }, { 0, 0, 1, 0 } },
			{ { 1.0f, 1.0f, 0.0f }, { 0, 1, 0, 0 } },
		},
//		{
//			{ { 0.0f, -1.0f, 1.0f }, { 0, 0, 1, 0 } },
//			{ { 0.0f, 1.0f, 0.0f }, { 1, 1, 1, 0 } },
//			{ { 0.0f, -1.0f, -1.0f }, { 0, 0, 1, 0 } },
//		}
};


float4x4 screenScaleT = float4x4::scale(float(width), float(height), 1.0f);
float4x4 screenTranslationT = float4x4::translation(float(width) / 2, float(height) / 2, 0);
float4x4 screenTransformT = screenTranslationT * screenScaleT;

static float rot = 0.0f;


int main(int argc, char* argv[])
{
	CScreen screen("Test", width, height);

//	camera.setCameraLookAtRH(float3(0, 0, -10), float3(0, 0, 0), float3(0, 1, 0));
//	std::cout << camera << std::endl;
//	std::cout << camera.transposed() << std::endl;

	screen.clear();

	float4x4 modelT, viewT, projectionT;
	float4x4 mvpT;

	Movement movement = { 0, 10, 0, 0, float(M_PI / 2) };

	while (screen.getUserInput(movement) != SCREEN_ACTION_QUIT)
	{
		screen.clear();

		rot += 0.001f;

//		modelT = float4x4::rotateAxis(float3(1, 1, 1).normalized(), (3.1415962f / 10) * rot);
		modelT = float4x4::identity();
		viewT = float4x4::cameraFirstPersonRH(float3(movement.x, 0, movement.y), 0, 0);
		projectionT = float4x4::projectionPerspective(movement.fov, float(width), float(height), 1.0f, 1000.0f);

		mvpT = projectionT * viewT * modelT;

		for (auto triangle : twoTriangleModel)
		{
			floattc triangleT = triangle;
			triangleT.vc0.v = screenTransformT.transform(mvpT.transform(triangle.vc0.v));
			triangleT.vc1.v = screenTransformT.transform(mvpT.transform(triangle.vc1.v));
			triangleT.vc2.v = screenTransformT.transform(mvpT.transform(triangle.vc2.v));
			screen.rasterize(triangleT);
		}
//		for (auto triangle : model)
//		{
//			floatt triangleT;
//			triangleT.v0.v = screenTransformT.transform(mvpT.transform(triangle.v0.v));
//			triangleT.v1.v = screenTransformT.transform(mvpT.transform(triangle.v1.v));
//			triangleT.v2.v = screenTransformT.transform(mvpT.transform(triangle.v2.v));
//			screen.draw(triangleT);
//		}
		//		for (auto triangle : plane)
		//			screen.draw(screenTransformT.transform(vpT.transform(triangle)));

		screen.update();
	}

	return 0;
}