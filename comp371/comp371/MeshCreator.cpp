#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"
#include "meshCreator.h"
#include "Chair.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

Mesh* MeshCreator::createChair()
{
	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	string model_path = "res/chair.3ds";
	std::ifstream fileStream(model_path, ios::in);

	if (fileStream.is_open())
	{
		string line = "";
		while (getline(fileStream, line))
		{
			//read line.
			std::istringstream iss(line); 

			bool gotHeader = false;
			unsigned int header = 0;
			for (std::string s; iss >> s;)
			{
				if (!gotHeader)
				{
					header = stoi(s);
					gotHeader = true;
				}
				else
				{
					switch (header)
					{
					case File_Header::VERTICES: // Vertices
						vertices.push_back(stof(s));
						break;
					case File_Header::POLYGON: //Indices
						indices.push_back(stoi(s));
						break;
					default:
						cout << "Unknow Header: " << header;
					}
				}
			}

			// get header
			// get points
		}
	}
	else {
		printf("Impossible to load model at path %s. Are you in the right directory ?\n", model_path.c_str());
		getchar();
		return nullptr;
	}
	return new Chair(vertices, indices);
}