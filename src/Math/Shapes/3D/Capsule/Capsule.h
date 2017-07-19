#pragma once

#include"../Line/Line3D.h"

struct Capsule
{
	Capsule();
	Capsule(const MyVector3& start, const MyVector3& end, float radius);
	Capsule(const MyVector3& start, float height, float radius);
	Capsule(const Line3D& line, float radius);

	void Translate(const MyVector3& position);

	Line3D m_line;
	float m_radius;
};