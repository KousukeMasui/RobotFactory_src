#include "MouseEffect.h"

#include<EffekseerForDXLib.h>
MouseEffect::MouseEffect():
	m_timer(0.0f),
	m_createTime(5.0f)
{
	m_effectHandle = LoadEffekseerEffect("res/Effect/click.efk");
}

MouseEffect::~MouseEffect()
{
}

void MouseEffect::Update(float deltaTime)
{
	m_timer -= deltaTime;
	UpdateEffekseer2D();
}

void MouseEffect::Draw() const
{
	DrawEffekseer2D();
}

void MouseEffect::Create(const MyVector2 & position)
{
	if (m_timer > 0.0f) return;
	int playHandle = PlayEffekseer2DEffect(m_effectHandle);
	SetPosPlayingEffekseer2DEffect(playHandle, position.x, position.y, 0.1f);

	m_timer = m_createTime;
}
