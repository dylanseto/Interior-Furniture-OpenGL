#include "Terrain.h"

Terrain::Terrain()
{
	this->type = Mesh_Type::TERRAIN;
}

void Terrain::render()
{
	this->draw();
}