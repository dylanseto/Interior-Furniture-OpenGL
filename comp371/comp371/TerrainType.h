#pragma once

#include <string>
using namespace std;

enum TerrainType
{
	TYPE_MOUNTAIN,
	TYPE_PARK
};

namespace TerrainHelper
{
	string getTextureValue(TerrainType type);
};