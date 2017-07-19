#include "Animation.h"
#include <stdarg.h>
#include"../../Sprite.h"
Animation::Animation(int cellNum, const MyVector2 & cellSize, float changeTime):
	m_index(0),
	m_timer(0.0f),
	m_changeTime(changeTime)
{
	for (int i = 0; i < cellNum; i++)
	{
		m_animationRect.push_back(MyRect(cellSize.x*i, 0.0f, cellSize.x * (i + 1), cellSize.y));
	}
}

Animation::Animation(float changeTime,int cellNum, ...) :
	m_index(0),
	m_timer(0.0f),
	m_changeTime(changeTime)
{
	va_list args;

	MyRect value;
	if (cellNum < 1) return;

	va_start(args, cellNum);

	for (int i = 0; i < cellNum; i++) {
		value = va_arg(args, MyRect);

		m_animationRect.push_back(value);
	}
	va_end(args);
}

Animation::~Animation()
{
}

bool Animation::OnUpdate(Sprite* sprite, float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_changeTime)
	{
		m_timer = 0.0f;
		m_index = (m_index + 1) % m_animationRect.size();
	}

	sprite->Rect(m_animationRect[m_index]);

	return false;
}
