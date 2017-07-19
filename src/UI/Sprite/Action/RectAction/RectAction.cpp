#include "RectAction.h"
#include"../../Sprite.h"
RectAction::RectAction(MyRect begin, MyRect end, float totalFrame):
	m_begin(begin),
	m_end(end),
	m_timer(0.0f),
	m_totalFrame(totalFrame)
{
}

RectAction::~RectAction()
{
}

bool RectAction::OnUpdate(Sprite* sprite, float deltaTime)
{
	m_timer += deltaTime;

	if (m_timer >= m_totalFrame)
	{
		m_timer = 0.0f;
		sprite->Rect(m_end);
		return true;
	}

	sprite->Rect(MyRect::Lerp(m_begin, m_end, m_timer / m_totalFrame));

	return false;
}
