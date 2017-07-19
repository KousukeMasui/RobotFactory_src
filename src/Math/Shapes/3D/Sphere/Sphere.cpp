#include "Sphere.h"
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
Sphere::Sphere(const MyVector3 & center, float radius):
	m_center(center),
	m_radius(radius)
{
}
bool Sphere::IsContains(const MyVector3 & target) const
{
	return MyVector3::Distance(m_center,target) <= m_radius;//”¼ŒaˆÈ“à‚ÉÀ•W‚ª‚ ‚Á‚½‚ç
}

bool Sphere::IsCollide(const Sphere & other) const
{
	return MyVector3::Distance(m_center, other.m_center) <= m_radius + other.m_radius;
}

HitInfo Sphere::IsCollide(const Line3D & line,float& t) const
{
	HitInfo hit;
	hit.isHit = line.PointLength(m_center) <= m_radius;

	MyVector3 d = MyVector3::Normalize(-line.Direction());

	d *= m_radius;

	hit.hitPosition = line.m_end - d;

	return hit;
}

HitInfo Sphere::IsCollide(const Capsule & capsule) const
{
	Sphere s(m_center, m_radius + capsule.m_radius);
	float t;
	return s.IsCollide(capsule.m_line,t);
}

Sphere Sphere::Transform(const MyMatrix4 & pose) const
{
	return Sphere(m_center * pose,m_radius * pose.GetScale().x);
}
