#include "Capsule.h"


Capsule::Capsule():
	m_line(MyVector3(),MyVector3()),
	m_radius(0.0f)
{
}

Capsule::Capsule(const MyVector3& start, const MyVector3& end, float radius) :
	m_line(start,end),
	m_radius(radius)
{
}

Capsule::Capsule(const MyVector3 & p, float height, float radius) :
	m_line(p, p + MyVector3(0,height,0)),
	m_radius(radius)
{
}

Capsule::Capsule(const Line3D & line, float radius) :
	m_line(line),
	m_radius(radius)
{
}

void Capsule::Translate(const MyVector3 & position)
{
	m_line.Translate(position);
}
