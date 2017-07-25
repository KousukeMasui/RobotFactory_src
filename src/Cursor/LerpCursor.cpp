#include "LerpCursor.h"
#include"Actor/Unit/Unit.h"
LerpCursor::LerpCursor(const MyVector3& position):
	SelectCursor(position),
	m_targetPosition(position),
	m_speed(5.0f)
{
}

LerpCursor::~LerpCursor()
{
}

void LerpCursor::SetPosition(const MyVector3 & position)
{
	m_targetPosition = position;
}

void LerpCursor::OnUpdate(float deltaTime)
{
	m_position += MyVector3(m_targetPosition - m_position).Normalize()* m_speed;
	m_position.y = 1.0f;
}

