#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\rotate_vector.hpp"
#include "gtc/type_ptr.hpp"
#include "meshCreator.h"
#include "Chair.h"
#include "Terrain.h"

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

		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;

			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			out_vertices.push_back(vertex.x);
			out_vertices.push_back(vertex.y);
			out_vertices.push_back(vertex.z);

		}
		else if (strcmp(lineHeader, "f") == 0){

			GLuint idx1, idx2, idx3, idx4; //3 indices per line

			int matches = fscanf(file, "%i %i %i %i \n", &idx1, &idx2, &idx3, &idx4);

			if (matches != 3){
				if (matches == 4)
				{
					//Then this is a quad.
					out_indices.push_back(idx1 - 1); //why -1? hint: look at the first index in teddy.obj
					out_indices.push_back(idx2 - 1);
					//out_indices.push_back(idx3 - 1);
					out_indices.push_back(idx4 - 1);

					out_indices.push_back(idx2 - 1); //why -1? hint: look at the first index in teddy.obj
					out_indices.push_back(idx3 - 1);
					out_indices.push_back(idx4 - 1);
				}
				else
				{
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					return false;
				}
			}
			else
			{
				out_indices.push_back(idx1 - 1); //why -1? hint: look at the first index in teddy.obj
				out_indices.push_back(idx2 - 1);
				out_indices.push_back(idx3 - 1);
			}
		}
		else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	return true;
}

void MeshCreator::createTerrain(vector<GLfloat> &vertices, vector<GLuint> &indices)
{
	for (int i = 0; i < Terrain::VERTEX_COUNT; i++)
	{
		for (int j = 0; j < Terrain::VERTEX_COUNT; j++)
		{
			vertices.push_back((float)j / ((float)Terrain::VERTEX_COUNT - 1) * Terrain::SIZE);
			vertices.push_back(0);
			vertices.push_back((float)i / ((float)Terrain::VERTEX_COUNT - 1) * Terrain::SIZE);
		}
	}

	for (int gz = 0; gz < Terrain::VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < Terrain::VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*Terrain::VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*Terrain::VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;

			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}
}