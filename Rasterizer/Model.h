#pragma once

#include <vector>

#include "color.h"
#include "triangle.h"


class CModel
{
private:
	std::vector<floattc> mvModel;
public:
	CModel();
	~CModel();

//	floattc* begin() { return &mvModel[0]; }
//	floattc* end() { return &mvModel[mvModel.size()]; }

	inline floattc operator[](int i) const { return mvModel[i]; }
	inline floattc& operator[](int i) { return mvModel[i]; }

	inline std::vector<floattc>& getTriangles(void) { return mvModel; }

	void addAxes(void);
	void addCubeRGB(float3 center, float3 side);
	void add(std::vector<floattc>& model);
	void addCheckerBoard(void);
};

