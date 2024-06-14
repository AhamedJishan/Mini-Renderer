#pragma once

#include <vector>

#include "vectors.h"

class Model
{
public:
	std::vector<Vec3f> vertices;
	std::vector<std::vector<int>> faces;

	Model(const char* filename);
	~Model();
};

