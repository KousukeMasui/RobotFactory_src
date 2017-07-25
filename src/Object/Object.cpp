#include "Object.h"
#include"Math/Converter.h"
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

bool Object::SlerpRotate(const MyVector3 & velocity, float deltaTime)
{
	//à⁄ìÆÇµÇ»Ç¢èÍçáâÒì]ÇçsÇÌÇ»Ç¢
	if (velocity.Length() <= FLT_EPSILON) return true;
	//velocityï˚å¸Ç…âÒì]Ç≥ÇπÇÈ
	Rotate(MyMatrix4::Lerp(m_rotate, MyMatrix4::SetForward(-velocity, MyVector3(0, 1, 0)), 0.1f));
	return Converter::RadToDeg(MyVector3::Angle(velocity, -m_rotate.GetForward())) <= 1.0f;
}