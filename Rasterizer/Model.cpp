#include "Model.h"


CModel::CModel()
{
}


CModel::~CModel()
{
}


void CModel::addAxes(void)
{
	//  x
	mvModel.push_back({ { { 1.1f, -0.1f, 0.1f }, red }, { { 1.1f, -0.1f, -0.1f }, red }, { { 2.0f, 0.0f, 0.0f }, black } });
	mvModel.push_back({ { { 1.1f, 0.1f, 0.1f }, red }, { { 1.1f, -0.1f, 0.1f }, red }, { { 2.0f, 0.0f, 0.0f }, black } });
	mvModel.push_back({ { { 1.1f, 0.1f, -0.1f }, red }, { { 1.1f, 0.1f, 0.1f }, red }, { { 2.0f, 0.0f, 0.0f }, black } });
	mvModel.push_back({ { { 1.1f, -0.1f, -0.1f }, red }, { { 1.1f, 0.1f, -0.1f }, red }, { { 2.0f, 0.0f, 0.0f }, black } });

	//  y
	mvModel.push_back({ { { -0.1f, 1.1f, -0.1f }, green }, { { -0.1f, 1.1f, 0.1f }, green }, { { 0.0f, 2.0f, 0.0f }, black } });
	mvModel.push_back({ { { -0.1f, 1.1f, 0.1f }, green }, { { 0.1f, 1.1f, 0.1f }, green }, { { 0.0f, 2.0f, 0.0f }, black } });
	mvModel.push_back({ { { 0.1f, 1.1f, 0.1f }, green }, { { 0.1f, 1.1f, -0.1f }, green }, { { 0.0f, 2.0f, 0.0f }, black } });
	mvModel.push_back({ { { 0.1f, 1.1f, -0.1f }, green }, { { -0.1f, 1.1f, -0.1f }, green }, { { 0.0f, 2.0f, 0.0f }, black } });

	//  z
	mvModel.push_back({ { { -0.1f, 0.1f, 1.1f }, blue }, { { -0.1f, -0.1f, 1.1f }, blue }, { { 0.0f, 0.0f, 2.0f }, black } });
	mvModel.push_back({ { { 0.1f, 0.1f, 1.1f }, blue }, { { -0.1f, 0.1f, 1.1f }, blue }, { { 0.0f, 0.0f, 2.0f }, black } });
	mvModel.push_back({ { { 0.1f, -0.1f, 1.1f }, blue }, { { 0.1f, 0.1f, 1.1f }, blue }, { { 0.0f, 0.0f, 2.0f }, black } });
	mvModel.push_back({ { { -0.1f, -0.1f, 1.1f }, blue }, { { 0.1f, -0.1f, 1.1f }, blue }, { { 0.0f, 0.0f, 2.0f }, black } });
}



void CModel::addCubeRGB(float3 center, float3 side)
{
	float3 hs000 = side / 2.0f;
	float3 hs001 = hs000 * float3(1, 1, -1);
	float3 hs010 = hs000 * float3(1, -1, 1);
	float3 hs011 = hs000 * float3(1, -1, -1);
	float3 hs100 = hs000 * float3(-1, 1, 1);
	float3 hs101 = hs000 * float3(-1, 1, -1);
	float3 hs110 = hs000 * float3(-1, -1, 1);
	float3 hs111 = hs000 * float3(-1, -1, -1);

	hs000 += center;
	hs001 += center;
	hs010 += center;
	hs011 += center;
	hs100 += center;
	hs101 += center;
	hs110 += center;
	hs111 += center;

	mvModel.push_back({ { hs111, white }, { hs101, magenta }, { hs001, blue } });
	mvModel.push_back({ { hs001, blue }, { hs011, cyan }, { hs111, white } });

	mvModel.push_back({ { hs100, red }, { hs110, yellow }, { hs000, black } });
	mvModel.push_back({ { hs010, green }, { hs000, black }, { hs110, yellow } });

	mvModel.push_back({ { hs110, yellow }, { hs111, white }, { hs010, green } });
	mvModel.push_back({ { hs011, cyan }, { hs010, green }, { hs111, white } });

	mvModel.push_back({ { hs101, magenta }, { hs100, red }, { hs000, black } });
	mvModel.push_back({ { hs000, black }, { hs001, blue }, { hs101, magenta } });

	mvModel.push_back({ { hs101, magenta }, { hs111, white }, { hs100, red } });
	mvModel.push_back({ { hs110, yellow }, { hs100, red }, { hs111, white } });

	mvModel.push_back({ { hs011, cyan }, { hs001, blue }, { hs000, black } });
	mvModel.push_back({ { hs000, black }, { hs010, green }, { hs011, cyan } });
}


void CModel::add(std::vector<floattc>& model)
{
	for (auto triangle : model)
		mvModel.push_back(triangle);
}

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


void CModel::addCheckerBoard(int dimension, float width)
{
	float middleOffset = (float(dimension) - 1.0f) * width / 2.0f;

	float halfWidth = width / 2.0f;
	float3 bl = float3(-halfWidth, 0, -halfWidth);
	float3 br = float3(halfWidth, 0, -halfWidth);
	float3 ul = float3(-halfWidth, 0, halfWidth);
	float3 ur = float3(halfWidth, 0, halfWidth);
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			float3 offset(float(x) * width - middleOffset, 0, float(y) * width - middleOffset);
			float4 color = ((x + y) % 2 == 1 ? black : white);
			mvModel.push_back({ { bl + offset, color }, { ul + offset, color }, { ur + offset, color } });
			mvModel.push_back({ { ur + offset, color }, { br + offset, color }, { bl + offset, color } });
		}
	}
}
