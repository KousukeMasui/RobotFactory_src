#include "Line3D.h"

#include"Math\Converter.h"

Line3D::Line3D(const MyVector3& start, const MyVector3& end) :
	m_start(start),
	m_end(end)
{
}

float Line3D::Length() const
{
	return Direction().Length();
}

MyVector3 Line3D::Direction() const
{
	return m_end - m_start;
}

float Line3D::PointLength(const MyVector3 & point) const
{
	MyVector3 v = Direction();//線の方向ベクトル
	MyVector3 v1 = point - m_start;//始点から球体への方向ベクトル

	float t = MyVector3::Dot(v, v1) / MyVector3::Dot(v, v);

	MyVector3 vt = t * v;
	MyVector3 vn = v1 - vt;

	//p1の外側か
	if (0 >= t)
	{
		return v1.Length();
	}
	MyVector3 v2 = point - m_end;
	if (t >= 1)//v2より外側
	{
		return v2.Length();
	}
	return vn.Length();
}

Line3D Line3D::Transform(const MyMatrix4 & matrix)
{
	return Line3D(m_start * matrix,m_end * matrix);
}

void Line3D::Translate(const MyVector3 & position)
{
	MyVector3 velocity = position - m_start;

	m_start += velocity;
	m_end += velocity;
}
