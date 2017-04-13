#pragma once

#include <glm.hpp>
#include <vector>
using namespace glm;
using namespace std;

enum RoomIntersectionType
{
	I_NONE,
	I_WALL,
	I_FLOOR,
	I_CEILING
};

enum PlayerActionType
{
	ACTION_UP,
	ACTION_DOWN,
	ACTION_RIGHT,
	ACTION_LEFT,
	ACTION_FORWARD,
	ACTION_BACKWARD,
};

namespace IntersectionHelper
{
	bool BoxToBoxIntersection(vector<glm::vec3> box1, vector<glm::vec3> box2);
	bool BoxToRoomIntersection(vector<glm::vec3> box, vector<glm::vec3> room, PlayerActionType type);
	RoomIntersectionType getRayRoomIntersection(vec3 ray, vector<glm::vec3> room, vec3 &intersection);
}