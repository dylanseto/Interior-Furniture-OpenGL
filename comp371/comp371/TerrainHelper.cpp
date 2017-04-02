#include "TerrainType.h"

#include <iostream>
using namespace std;

string TerrainHelper::getTextureValue(TerrainType type)
{
	switch (type)
	{
	case TYPE_MOUNTAIN:
		return "mountain";
	case TYPE_PARK:
		return "park";
	default:
		cout << "[ERROR] Unknown SkyBox Texture Type. Defaulting To Mountains." << endl;
		return "mountain";
	}
}