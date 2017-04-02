#include "Terrain.h"
#include "MeshCreator.h"
#include "Game.h"
#include <iostream>


Terrain::Terrain()
{
	this->type = Mesh_Type::TERRAIN;
	this->texture = TerrainType::TYPE_MOUNTAIN;

	//UVs and normals are unused, so just send the function dummy vectors
	if (MeshCreator::loadCube(this->vertices, vector<GLfloat>(), vector<GLfloat>()))
	{
		cout << "[LOAD] Loaded SkyBox." << endl;
		this->updateBuffer();

		this->updateMatrix();
	}
}

void Terrain::render()
{
	this->draw();
}

void Terrain::draw()
{
	//std::cout << "draw" << std::endl;
	glUseProgram(shaderProgram);
	glm::mat4 skybox_view = glm::mat4(glm::mat3(Game::getInstance()->getView())); //remove the translation data

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view_matrix"), 1, GL_FALSE, glm::value_ptr(skybox_view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection_matrix"), 1, GL_FALSE, glm::value_ptr(Game::getInstance()->getProjection()));

	glUniform1i(glGetUniformLocation(shaderProgram, "skyboxTexture"), 0); //use texture unit 0

	glDepthMask(GL_FALSE);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}

void Terrain::updateBuffer()
{
	std::cout << "buffer" << std::endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glActiveTexture(GL_TEXTURE0);
	GLuint cubemapTexture = MeshCreator::createTerrain(TerrainHelper::getTextureValue(texture));
	cout << "[Load] Loaded SkyBox texture." << endl;
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}