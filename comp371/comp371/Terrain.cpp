#include "Terrain.h"
#include "MeshCreator.h"


Terrain::Terrain()
{
	this->type = Mesh_Type::TERRAIN;
	MeshCreator::createTerrain(this->vertices, this->indices);
	this->updateBuffer();
}

void Terrain::render()
{
	this->draw();
}