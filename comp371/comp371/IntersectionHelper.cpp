#include "IntersectionHelper.h"
#include <iostream>
using namespace std;

bool IntersectionHelper::BoxToBoxIntersection(vector<glm::vec3> box1, vector<glm::vec3> box2)
{
	return false;
}

bool IntersectionHelper::BoxToRoomIntersection(vector<glm::vec3> box, vector<glm::vec3> room, PlayerActionType action)
{
	cout << "Box0: " << box[0].x - (box[0].x - box[2].x) << endl;
	cout << "Box1: " << box[1].x - (box[0].x - box[2].x) << endl;
	cout << "Box4: " << box[4].x - (box[0].x - box[2].x) << endl;
	cout << "Box5: " << box[5].x - (box[0].x - box[2].x) << endl;
	cout << "Room: " << room[0].x << endl;

	if (action == PlayerActionType::ACTION_UP)
	{
		//Ceiling collision
		if (box[0].y - (box[0].y - box[1].y) >= room[0].y
			|| box[3].y - (box[0].y - box[1].y) >= room[3].y
			|| box[4].y - (box[0].y - box[1].y) >= room[4].y
			|| box[7].y - (box[0].y - box[1].y) >= room[7].y)
		{
			return true;
		}
		return false;
	}
	else if (action == PlayerActionType::ACTION_DOWN)
	{
		//Floor collision
		if (box[1].y + (box[0].y - box[1].y) <= room[1].y
			|| box[2].y + (box[0].y - box[1].y) <= room[2].y
			|| box[5].y + (box[0].y - box[1].y) <= room[5].y
			|| box[6].y + (box[0].y - box[1].y) <= room[6].y)
		{
			return true;
		}
		return false;
	}
	else if (action == PlayerActionType::ACTION_LEFT)
	{
		if (box[2].x + (box[0].x - box[2].x) <= room[2].x
			|| box[3].x + (box[0].x - box[2].x) <= room[3].x
			|| box[6].x + (box[0].x - box[2].x) <= room[6].x
			|| box[7].x + (box[0].x - box[2].x) <= room[7].x)
		{
			return true;
		}
		return false;
	}
	else if (action == PlayerActionType::ACTION_RIGHT)
	{
		if (box[0].x - (box[0].x - box[2].x) >= room[0].x
			|| box[1].x - (box[0].x - box[2].x) >= room[1].x
			|| box[4].x - (box[0].x - box[2].x) >= room[4].x
			|| box[5].x - (box[0].x - box[2].x) >= room[5].x)
		{
			return true;
		}
		return false;
	}
	else if (action == PlayerActionType::ACTION_FORWARD)
	{
		if (box[0].z - (box[0].x - box[4].x) >= room[0].z
			|| box[1].z - (box[0].x - box[4].x) >= room[1].z
			|| box[2].z - (box[0].x - box[4].x) >= room[2].z
			|| box[3].z - (box[0].x - box[4].x) >= room[3].z)
		{
			return true;
		}
		return false;
	}
	else if (action == PlayerActionType::ACTION_BACKWARD)
	{
		if (box[4].z + (box[0].x - box[4].x) >= room[4].z
			|| box[5].z + (box[0].x - box[4].x) >= room[5].z
			|| box[6].z + (box[0].x - box[4].x) >= room[6].z
			|| box[7].z + (box[0].x - box[4].x) >= room[7].z)
		{
			return true;
		}
		return false;
	}
	return false;
}

RoomIntersectionType IntersectionHelper::getRayRoomIntersection(vec3 ray, vector<glm::vec3> room, vec3 &intersection)
{
	return RoomIntersectionType::I_NONE;
}