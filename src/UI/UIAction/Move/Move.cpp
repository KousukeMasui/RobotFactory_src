#include "Move.h"
#include"../../UI.h"
Move::Move(const MyVector2 & begin, const MyVector2 & end, float totalFrame):
	m_begin(begin),
	m_end(end),
	m_totalFrame(totalFrame),
	m_timer(0.0f)
{
}

Move::~Move()
{
}

bool Move::Update(UI* ui, float deltaTime)
{
	m_timer = std::fminf(m_timer + deltaTime, m_totalFrame);

	ui->Position(MyVector2::Lerp(m_begin, m_end, std::fminf((m_timer / m_totalFrame), 1.0f)));
	if (std::abs(m_timer - m_totalFrame) <= FLT_EPSILON)
	{
		m_timer = 0.0f;
		return true;
	}
	return false;
}
