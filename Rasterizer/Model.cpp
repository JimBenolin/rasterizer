#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


CModel::CModel()
{
}


CModel::~CModel()
{
}


void CModel::addSingle(void)
{
	mvModel.push_back({ { { 0, 0, -1 }, red }, { { -1, 0, 1 }, green }, { { 1, 0, 1 }, blue } });
	addAxes();
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

void PrintInfo(const std::vector<tinyobj::shape_t>& shapes, const std::vector<tinyobj::material_t>& materials);
bool CModel::loadOBJ(const std::string& name)
{
	CFilename filename(name);

	std::string files = filename.toString();
	const char* file = files.c_str();
	const char* path = filename.getPath().c_str();

	std::cout << "Loading " << filename << std::endl;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	char* basepath = 0;
	bool ret = tinyobj::LoadObj(shapes, materials, err, filename.c_str(), basepath);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		return false;
	}

	PrintInfo(shapes, materials);

	return true;
}


static void PrintInfo(const std::vector<tinyobj::shape_t>& shapes, const std::vector<tinyobj::material_t>& materials)
{
	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;

	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
		assert((shapes[i].mesh.indices.size() % 3) == 0);
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		assert((shapes[i].mesh.positions.size() % 3) == 0);
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}

	for (size_t i = 0; i < materials.size(); i++) {
		printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
		printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
		printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
		printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
		printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
		printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
		printf("  material.Ns = %f\n", materials[i].shininess);
		printf("  material.Ni = %f\n", materials[i].ior);
		printf("  material.dissolve = %f\n", materials[i].dissolve);
		printf("  material.illum = %d\n", materials[i].illum);
		printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
		printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
		printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
		printf("  material.map_Ns = %s\n", materials[i].specular_highlight_texname.c_str());
		printf("  material.map_bump = %s\n", materials[i].bump_texname.c_str());
		printf("  material.map_d = %s\n", materials[i].alpha_texname.c_str());
		printf("  material.disp = %s\n", materials[i].displacement_texname.c_str());
		std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
		std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
		for (; it != itEnd; it++) {
			printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
		}
		printf("\n");
	}
}
