#include "LerpCursor.h"
#include"Actor/Unit/Unit.h"
LerpCursor::LerpCursor(const MyVector3& position):
	SelectCursor(position)
{
}

LerpCursor::~LerpCursor()
{
}

void LerpCursor::Update(const MyVector3 & position, float deltaTime)
{
	m_position = MyVector3::Lerp(m_position, position, 0.1f * deltaTime);
	m_position.y = 1.0f;
	m_sphere.m_center = m_position;
}

