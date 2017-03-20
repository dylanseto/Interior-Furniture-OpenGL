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

#pragma warning(disable:4996)

bool MeshCreator::loadOBJ(string path, std::vector<GLfloat> & out_vertices, std::vector<GLuint> & out_indices)
{
	printf("Loading OBJ file %s...\n", ("res/" + path).c_str());

	FILE * file = fopen(("res/" + path).c_str(), "r");

	if (file == NULL){
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while (1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, File_Header::VERTICES.c_str()) == 0){
			glm::vec3 vertex;

			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			out_vertices.push_back(vertex.x);
			out_vertices.push_back(vertex.y);
			out_vertices.push_back(vertex.z);

		}
		else if (strcmp(lineHeader, File_Header::INDICES.c_str()) == 0){

			GLuint idx1, idx2, idx3; //3 indices per line

			int matches = fscanf(file, "%i %i %i \n", &idx1, &idx2, &idx3);

			if (matches != 3){
				cout << idx1 << endl;
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}

			out_indices.push_back(idx1 - 1); //why -1? hint: look at the first index in teddy.obj
			out_indices.push_back(idx2 - 1);
			out_indices.push_back(idx3 - 1);

		}
		else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	return true;
}

/*Mesh* MeshCreator::createChair()
{
	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	string model_path = "res/chair.obj";
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
}*/