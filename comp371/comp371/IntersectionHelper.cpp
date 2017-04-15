#include "IntersectionHelper.h"
#include <iostream>
using namespace std;

bool IntersectionHelper::BoxToBoxIntersection(vector<glm::vec3> box1, vector<glm::vec3> box2)
{
	cout << "box1: " << box1[2].x << endl;
	cout << "box1: " << box1[0].x << endl;
	cout << "box2: " << box2[2].x << endl;
	cout << "box2: " << box2[0].x << endl;
	cout << "box2: " << box2[1].x << endl;
	cout << "box2: " << box2[4].x << endl;
	cout << "box2: " << box2[5].x << endl;
	/*
	Condiitons for no overlap, either one of these:

	Cond1.If A's left face is to the right of the B's right face,
	-then A is Totally to right Of B
	CubeA.X2 < CubeB.X1
	Cond2.If A's right face is to the left of the B's left face,
	-then A is Totally to left Of B
	CubeB.X2 < CubeA.X1
	Cond3.If A's top face is below B's bottom face,
	-then A is Totally below B
	CubeA.Z2 < CubeB.Z1
	Cond4.If A's bottom face is above B's top face,
	-then A is Totally above B
	CubeB.Z2 < CubeA.Z1
	Cond5.If A's front face is behind B's back face,
	-then A is Totally behind B
	CubeB.Y2 < CubeA.Y1
	Cond6.If A's left face is to the left of B's right face,
	-then A is Totally to the right of B
	CubeB.X2 < CubeA.X1
	*/

	//Condition 1
	if (box1[0].x < box2[2].x
		&& box1[0].x  < box2[3].x
		&& box1[0].x < box2[6].x
		&& box1[0].x < box2[7].x

		&& box1[1].x < box2[2].x
		&& box1[1].x < box2[3].x
		&& box1[1].x < box2[6].x
		&& box1[1].x < box2[7].x

		&& box1[4].x < box2[2].x
		&& box1[4].x < box2[3].x
		&& box1[4].x < box2[6].x
		&& box1[4].x < box2[7].x

		&& box1[5].x < box2[2].x
		&& box1[5].x < box2[3].x
		&& box1[5].x < box2[6].x
		&& box1[5].x < box2[7].x)
	{
		cout << "con1" << endl;
		return false;
	}
	//Condiiton 2
	else if (box1[2].x > box2[0].x
		&& box1[2].x > box2[1].x
		&& box1[2].x > box2[4].x
		&& box1[2].x > box2[5].x

		&& box1[3].x > box2[0].x
		&& box1[3].x > box2[1].x
		&& box1[3].x > box2[4].x
		&& box1[3].x > box2[5].x

		&& box1[6].x > box2[0].x
		&& box1[6].x > box2[1].x
		&& box1[6].x > box2[4].x
		&& box1[6].x > box2[5].x

		&& box1[7].x  > box2[0].x
		&& box1[7].x  > box2[1].x
		&& box1[7].x > box2[4].x
		&& box1[7].x > box2[5].x)
	{
		cout << "con2" << endl;
		return false;
	}
	//Condiiton 3

	else if (box1[0].y < box2[1].y
		&& box1[0].y < box2[2].y
		&& box1[0].y < box2[5].y
		&& box1[0].y < box2[6].y

		&& box1[3].y < box2[1].y
		&& box1[3].y < box2[2].y
		&& box1[3].y < box2[5].y
		&& box1[3].y < box2[6].y

		&& box1[4].y < box2[1].y
		&& box1[4].y < box2[2].y
		&& box1[4].y < box2[5].y
		&& box1[4].y < box2[6].y

		&& box1[7].y  < box2[1].y
		&& box1[7].y < box2[2].y
		&& box1[7].y < box2[5].y
		&& box1[7].y < box2[6].y)
	{
		cout << "con3" << endl;
		return false;
	}
	//Condiiton 4
	else if (box1[1].y > box2[0].y
		&& box1[1].y > box2[3].y
		&& box1[1].y > box2[4].y
		&& box1[1].y > box2[7].y

		&& box1[2].y > box2[0].y
		&& box1[2].y > box2[3].y
		&& box1[2].y > box2[4].y
		&& box1[2].y > box2[7].y

		&& box1[5].y > box2[0].y
		&& box1[5].y > box2[3].y
		&& box1[5].y > box2[4].y
		&& box1[5].y > box2[7].y

		&& box1[6].y > box2[0].y
		&& box1[6].y > box2[3].y
		&& box1[6].y > box2[4].y
		&& box1[6].y > box2[7].y)
	{
		cout << "con4" << endl;
		return false;
	}
	//Condition 5
	else if (box1[0].z < box2[4].z
		&& box1[0].z < box2[5].z
		&& box1[0].z < box2[6].z
		&& box1[0].z < box2[7].z

		&& box1[1].z < box2[4].z
		&& box1[1].z < box2[5].z
		&& box1[1].z < box2[6].z
		&& box1[1].z < box2[7].z

		&& box1[2].z < box2[4].z
		&& box1[2].z < box2[5].z
		&& box1[2].z < box2[6].z
		&& box1[2].z < box2[7].z

		&& box1[3].z < box2[4].z
		&& box1[3].z < box2[5].z
		&& box1[3].z < box2[6].z
		&& box1[3].z < box2[7].z)
	{
		cout << "con5" << endl;
		return false;
	}
	//Condition 6
	else if (box1[4].z > box2[0].z
		&& box1[4].z > box2[1].z
		&& box1[4].z > box2[2].z
		&& box1[4].z > box2[3].z

		&& box1[5].z > box2[0].z
		&& box1[5].z > box2[1].z
		&& box1[5].z > box2[2].z
		&& box1[5].z > box2[3].z

		&& box1[6].z > box2[0].z
		&& box1[6].z > box2[1].z
		&& box1[6].z > box2[2].z
		&& box1[6].z > box2[3].z

		&& box1[7].z > box2[0].z
		&& box1[7].z > box2[1].z
		&& box1[7].z > box2[2].z
		&& box1[7].z > box2[3].z)
	{
		cout << "con6" << endl;
		return false;
	}
	//Non of thes conditions, therefore intersects.
	else
	{
		cout << "wtf" << endl;
		return true;
	}
}

bool IntersectionHelper::BoxToRoomIntersection(vector<glm::vec3> box, vector<glm::vec3> room, PlayerActionType action)
{
	if (action == PlayerActionType::ACTION_UP)
	{
		cout << box[0].y << endl;
		//Ceiling collision
		if (box[0].y >= room[0].y
			|| box[3].y >= room[3].y
			|| box[4].y >= room[4].y
			|| box[7].y >= room[7].y)
		{
			return true;
		}
		return false;
	}
	else if (action == PlayerActionType::ACTION_DOWN)
	{
		cout << box[1].y << endl;
		cout << room[1].y << endl;
		cout << "difference: " << (box[0].y - box[1].y) << endl;
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
	// Ceiling
	vec3 CeilingNorm;
	// Wall 1
	vec3 Wall1Norm;
	// Wall 2
	vec3 Wall2Norm;
	// Wall 3
	vec3 Wall3Norm;
	// Wall 4
	vec3 Wall4Norm;
	// Floor
	vec3 FloorNorm;

	return RoomIntersectionType::I_NONE;
}

vector<vec3> IntersectionHelper::createBoundingBox(vector<float> vertices, mat4 modelMatrix)
{
	vector<vec3> boundingBox;

	float xMax = -2;
	float xMin = 2;
	float yMax = -2;
	float yMin = 2;
	float zMax = -2;
	float zMin = 2;

	for (int i = 0; i != vertices.size(); i += 3)
	{
		vec3 point = vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		vec3 pointTransformed = modelMatrix*vec4(point, 1);

		float x = pointTransformed.x;
		float y = pointTransformed.y;
		float z = pointTransformed.z;

		if (x > xMax) xMax = x;
		else if (x < xMin) xMin = x;

		if (y > yMax) yMax = y;
		else if (y < yMin) yMin = y;

		if (z > zMax) zMax = z;
		else if (z < zMin) zMin = z;
	}

	//Front face of bounding box.
	boundingBox.push_back(vec4(xMax, yMax, zMax, 1));
	boundingBox.push_back(vec4(xMax, yMin, zMax, 1));
	boundingBox.push_back(vec4(xMin, yMin, zMax, 1));
	boundingBox.push_back(vec4(xMin, yMax, zMax, 1));

	//Back
	boundingBox.push_back(vec4(xMax, yMax, zMin, 1));
	boundingBox.push_back(vec4(xMax, yMin, zMin, 1));
	boundingBox.push_back(vec4(xMin, yMin, zMin, 1));
	boundingBox.push_back(vec4(xMin, yMax, zMin, 1));

	return boundingBox;
}