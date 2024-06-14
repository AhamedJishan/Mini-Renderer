#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Model::Model(const char* filename)
{
	std::ifstream in;
	in.open(filename, std::ios::in);
	if (!in.is_open())
	{
		std::cout << "Failed to open the obj file!\n";
	}

	std::string line;
	while (std::getline(in, line))
	{
		std::istringstream iss(line);
		char type;
		iss >> type;

		if (type == 'v')
		{
			float x, y, z;
			iss >> x >> y >> z;
			vertices.emplace_back(Vec3f(x, y, z));
		}
		else if (type == 'f')
		{
			std::vector<int> face;
			int faceIndex;
			std::string extradata;
			do
			{
				if(iss >> faceIndex)
					face.emplace_back(faceIndex);
			} while (iss >> extradata);
			faces.emplace_back(face);
		}
	}
}

Model::~Model()
{
}
