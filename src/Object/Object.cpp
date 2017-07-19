#include "Object.h"

Object::Object(const MyVector3& position, const MyMatrix4& rotate):
	m_position(position),
	m_rotate(rotate)
{
}

MyVector3 Object::Position() const
{
	return m_position;
}
MyVector3 * Object::PositionPtr()
{
	return &m_position;
}
MyMatrix4 Object::Rotate() const
{
	return m_rotate;
}

void Object::Position(const MyVector3 & position)
{
	m_position = position;
}

void Object::Rotate(const MyMatrix4 & rotate)
{
	m_rotate = rotate;
}

MyMatrix4 Object::GetPose() const
{
	return MyMatrix4(m_rotate).SetPosition(m_position);
}
