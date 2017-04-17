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
	bool rayBoxIntersection(vec3 ray, vector<glm::vec3> box, vec3 &intersection);
	vector<vec3> createBoundingBox(vector<glm::vec3> vertices, mat4 modelMatrix);
	bool planeIntersection(vec3 ray, vec3 nor, vec3 pos, vec3 &intersection);
}