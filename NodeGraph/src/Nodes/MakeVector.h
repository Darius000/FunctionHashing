#pragma once

#include "Node.h"


class MakeVector2 : public Node
{
public:

	MakeVector2() : x(0.0f), y(0.0f) {}

	float x;

	float y;

	glm::vec2 GetVec() { return glm::vec2(x, y); }

	REFLECTABLEV(Node)

};

class MakeVector3 : public Node
{
public:
	MakeVector3() : x(0.0f), y(0.0f) , z(0.0f) {}

	float x;

	float y;

	float z;

	glm::vec3 GetVec() { return glm::vec3(x, y, z); }

	REFLECTABLEV(Node)
};

class MakeVector4 : public Node
{
public:

	MakeVector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	float x;

	float y;

	float z;

	float w;

	glm::vec4 GetVec() { return glm::vec4(x, y, z, w); }

	REFLECTABLEV(Node)
};

class BreakVector2 : public Node
{
public:

	BreakVector2() : vec() {}

	glm::vec2 vec;

	float GetX() { return vec.x; }

	float GetY() { return vec.y; }

	REFLECTABLEV(Node)

};

class BreakVector3 : public Node
{
public:

	BreakVector3() : vec() {}

	glm::vec3 vec;

	float GetX() { return vec.x; }

	float GetY() { return vec.y; }

	float GetZ() { return vec.z; }

	REFLECTABLEV(Node)

};

class BreakVector4 : public Node
{
public:

	BreakVector4() : vec() {}

	glm::vec4 vec;

	float GetX() { return vec.x; }

	float GetY() { return vec.y; }

	float GetZ() { return vec.z; }

	float GetW() { return vec.w; }

	REFLECTABLEV(Node)

};