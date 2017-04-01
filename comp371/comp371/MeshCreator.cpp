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
#include <SOIL.h>

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

bool MeshCreator::loadCube(vector<GLfloat> &vertices, vector<GLfloat> normals, vector<GLfloat> uvs)
{
	std::cout << "Loading skybox cube..." << endl;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen("res/cube.obj", "r");
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

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);

		uvs.push_back(uv.x);
		uvs.push_back(uv.y);

		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);

	}

	return true;
}

GLuint MeshCreator::createTerrain (string textureName)
{
	std::cout << "Texture: " << textureName << endl;
	vector<string> faces;
	faces.push_back("res/" + textureName + "/right.jpg");
	faces.push_back("res/" + textureName +"/left.jpg");
	faces.push_back("res/" + textureName + "/top.jpg");
	faces.push_back("res/" + textureName + "/bottom.jpg");
	faces.push_back("res/" + textureName + "/back.jpg");
	faces.push_back("res/" + textureName + "/front.jpg");

	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);

		SOIL_free_image_data(image); //free resources
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}