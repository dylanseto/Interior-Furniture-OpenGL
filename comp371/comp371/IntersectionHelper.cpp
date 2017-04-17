#include "IntersectionHelper.h"
#include <iostream>
#include <glm.hpp>
using namespace std;
using namespace glm;

bool IntersectionHelper::BoxToBoxIntersection(vector<glm::vec3> box1, vector<glm::vec3> box2)
{
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
		return false;
	}
	//Non of thes conditions, therefore intersects.
	else
	{
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
	vec3 v1 = room[3] - room[0];
	vec3 v2 = room[4] - room[0];
	vec3 CeilingNor = glm::cross(v1, v2);

		//Plane intersection
	vec3 ceilingIntersection;
	bool planeInter = planeIntersection(ray, CeilingNor, room[4], ceilingIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (ceilingIntersection.x < 1 && ceilingIntersection.x > -1
			&& glm::floor(ceilingIntersection.y) == 1
			&& ceilingIntersection.z < 1 && ceilingIntersection.z > -1)
		{
			intersection = ceilingIntersection;
			RoomIntersectionType::I_CEILING;
		}
	}


	// Wall 1 - front
	v1 = room[1] - room[0];
	v2 = room[2] - room[0];
	vec3 Wall1Nor = glm::cross(v1, v2);


	vec3 wall1Intersection;
	planeInter = planeIntersection(ray, Wall1Nor, room[2], wall1Intersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (wall1Intersection.x < 1 && wall1Intersection.x > -1
			&& wall1Intersection.y < 1 && wall1Intersection.y > -1
			&& glm::floor(wall1Intersection.z) == 1)
		{
			intersection = wall1Intersection;
			RoomIntersectionType::I_WALL;
		}
	}
	// Wall 2 - back
	v1 = room[5] - room[4];
	v2 = room[6] - room[4];
	vec3 Wall2Nor = glm::cross(v1, v2);


	vec3 wall2Intersection;
	planeInter = planeIntersection(ray, Wall2Nor, room[4], wall2Intersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (wall2Intersection.x < 1 && wall2Intersection.x > -1
			&& wall2Intersection.y < 1 && wall2Intersection.y > -1
			&& glm::floor(wall2Intersection.z) == -1)
		{
			intersection = wall2Intersection;
			RoomIntersectionType::I_WALL;
		}
	}
	// Wall 3 - right
	v1 = room[0] - room[4];
	v2 = room[1] - room[4];
	vec3 Wall3Nor = glm::cross(v1, v2);

	vec3 wall3Intersection;
	planeInter = planeIntersection(ray, Wall3Nor, room[4], wall3Intersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (glm::floor(wall3Intersection.x) == 1
			&& wall3Intersection.y < 1 && wall3Intersection.y > -1
			&& wall3Intersection.z < 1 && wall3Intersection.z > -1)
		{
			intersection = wall3Intersection;
			RoomIntersectionType::I_WALL;
		}
	}
	// Wall 4 - left
	v1 = room[2] - room[6];
	v2 = room[3] - room[6];
	vec3 Wall4Nor = glm::cross(v1, v2);

	vec3 wall4Intersection;
	planeInter = planeIntersection(ray, Wall4Nor, room[6], wall4Intersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (glm::floor(wall4Intersection.x) == -1
			&& wall4Intersection.y < 1 && wall4Intersection.y > -1
			&& wall4Intersection.z < 1 && wall4Intersection.z > -1)
		{
			intersection = wall4Intersection;
			RoomIntersectionType::I_WALL;
		}
	}
	// Floor
	v1 = room[2] - room[1];
	v2 = room[5] - room[1];
	vec3 FloorNor = glm::cross(v2, v1);

	vec3 floorIntersection;
	planeInter = planeIntersection(ray, FloorNor, room[2], floorIntersection);

	if (planeInter)
	{
		cout << "floor pos: " << floorIntersection.x << " " << floorIntersection.y << " " << floorIntersection.z << endl;
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (floorIntersection.x < 1 && floorIntersection.x > -1
			&& glm::floor(floorIntersection.y) == -1.0f
			&& floorIntersection.z < 1 && floorIntersection.z > -1)
		{
			cout << "Floor" << endl;
			intersection = floorIntersection;
			cout << intersection.x << " " << intersection.y << " " << intersection.z << endl;
			RoomIntersectionType::I_FLOOR;
		}
		else
		{
			cout << (floorIntersection.x < 1) << endl;
			cout << (floorIntersection.x > -1) << endl;
			cout << (floorIntersection.z < 1) << endl;
			cout << (floorIntersection.z > -1) << endl;
			cout << (glm::floor(floorIntersection.y) == -1.0f) << endl;
			cout << (floorIntersection.y) << endl;
		}
	}

	// Made it this far, that means there's no intersection with any side of the room? WEIRD
	// This Should never happen, it's only here for completeness.
	return RoomIntersectionType::I_NONE; 
}

bool IntersectionHelper::rayBoxIntersection(vec3 ray, vector<glm::vec3> box, vec3 &intersection)
{
	float maxX = box[0].x;
	float minX = box[2].x;
	float maxY = box[0].y;
	float minY = box[1].y;
	float maxZ = box[0].z;
	float minZ = box[5].z;

	float yDif = minY + 1;

	// Top
	vec3 v1 = box[3] - box[0];
	vec3 v2 = box[4] - box[0];
	vec3 TopNor = glm::cross(v1, v2);

	//Plane intersection
	vec3 topIntersection;
	bool planeInter = planeIntersection(ray, TopNor, box[4], topIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (topIntersection.x <= maxX && topIntersection.x >= minY
			&& (glm::ceil(topIntersection.y) == glm::ceil(maxY))
			&& topIntersection.z <= maxZ && topIntersection.z >= minZ)
		{
			intersection = topIntersection;
			return true;
		}
	}


	// front
	v1 = box[1] - box[0];
	v2 = box[2] - box[0];
	vec3 frontNor = glm::cross(v1, v2);


	vec3 frontIntersection;
	planeInter = planeIntersection(ray, frontNor, box[2], frontIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (frontIntersection.x < maxX && frontIntersection.x > minX
			&& frontIntersection.y < maxY && frontIntersection.y > minY
			&& (glm::ceil(frontIntersection.z) == glm::ceil(maxZ)))
		{
			intersection = frontIntersection;
			return true;
		}
	}
	// back
	v1 = box[5] - box[4];
	v2 = box[6] - box[4];
	vec3 backNor = glm::cross(v1, v2);


	vec3 backIntersection;
	planeInter = planeIntersection(ray, backNor, box[4], backIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (backIntersection.x < maxX && backIntersection.x > minX
			&& backIntersection.y < maxY && backIntersection.y > minY
			&& (glm::ceil(backIntersection.z) == glm::ceil(minZ)))
		{
			intersection = backIntersection;
			return true;
		}
	}
	// Wall 3 - right
	v1 = box[0] - box[4];
	v2 = box[1] - box[4];
	vec3 rightNor = glm::cross(v1, v2);

	vec3 rightIntersection;
	planeInter = planeIntersection(ray, rightNor, box[4], rightIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if ((glm::ceil(rightIntersection.x) == glm::ceil(maxX))
			&& rightIntersection.y < maxY && rightIntersection.y > minY
			&& rightIntersection.z < maxZ && rightIntersection.z > minZ)
		{
			intersection = rightIntersection;
			return true;
		}
	}
	// Wall 4 - left
	v1 = box[2] - box[6];
	v2 = box[3] - box[6];
	vec3 leftNor = glm::cross(v1, v2);

	vec3 leftIntersection;
	planeInter = planeIntersection(ray, leftNor, box[6], leftIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if ((glm::ceil(leftIntersection.x) == glm::ceil(minX))
			&& leftIntersection.y < maxY && leftIntersection.y > minY
			&& leftIntersection.z < maxZ && leftIntersection.z > minZ)
		{
			intersection = leftIntersection;
			return true;
		}
	}
	// Floor
	v1 = box[2] - box[1];
	v2 = box[5] - box[1];
	vec3 bottomNor = glm::cross(v2, v1);

	vec3 bottomIntersection;
	planeInter = planeIntersection(ray, bottomNor, box[2], bottomIntersection);

	if (planeInter)
	{
		//Check if intersection point is in rectangle, if it is, return ceiling type.
		if (bottomIntersection.x < maxX && bottomIntersection.x > minX
			&& (glm::ceil(bottomIntersection.y) == glm::ceil(minY))
			&& bottomIntersection.z < maxZ && bottomIntersection.z > minZ)
		{
			intersection = bottomIntersection;
			return true;
		}
	}

	return false;
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

bool IntersectionHelper::planeIntersection(vec3 ray, vec3 nor, vec3 pos, vec3 &intersection)
{
	if (dot(ray, pos) != 0) //Not parallel so they'll intersect.
	{
		vec3 intersectionPoint;
		float m = (nor.x*(pos.x) + nor.y*(pos.y) + nor.z*(pos.z))
			/ (ray.x*nor.x + ray.y*nor.y + ray.z*nor.z);

		intersectionPoint.x = ray.x*m;
		intersectionPoint.y = ray.y*m;
		intersectionPoint.z = ray.z*m;


		if (m < 0) // Intersection is behind Camera
		{
			return -1;
		}

		intersection = intersectionPoint;

		return true;
	}

	return false;
}