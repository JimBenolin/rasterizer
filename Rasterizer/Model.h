#pragma once

#include <vector>

#include "color.h"
#include "triangle.h"
#include "Filename.h"


class CModel
{
private:
	std::vector<floattc> mvModel;
	float4x4 mTransform;
public:
	CModel();
	~CModel();

	inline floattc operator[](int i) const { return mvModel[i]; }
	inline floattc& operator[](int i) { return mvModel[i]; }

	inline std::vector<floattc>& getTriangles(void) { return mvModel; }

	void addAxes(void);
	void addCubeRGB(float3 center, float3 side);
	void add(std::vector<floattc>& model);
	void addSingle(void);
	void addCheckerBoard(int dimension = 10, float width = 1.0f);

	bool loadOBJ(const std::string& name);
};

