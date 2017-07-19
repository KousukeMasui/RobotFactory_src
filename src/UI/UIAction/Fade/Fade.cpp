#include "Fade.h"
#include"Math\MyMath.h"
#include<DxLib.h>
#include"../../UI.h"
Fade::Fade(float begin, float end, float totalFrame):
	m_begin(begin),
	m_end(end),
	m_totalFrame(totalFrame),
	m_timer(0.0f)
{
}

Fade::~Fade()
{
}

bool Fade::Update(UI* ui, float deltaTime)
{
	m_timer = std::fminf(m_timer +deltaTime,m_totalFrame);
	auto color = ui->GetColor();
	color.a =MyMath::Lerp(m_begin, m_end, std::fminf((m_timer / m_totalFrame),1.0f));
	ui->SetColor(color);
	if (std::abs(m_timer - m_totalFrame) <= FLT_EPSILON)
	{
		m_timer = 0.0f;
		return true;
	}
	return false;
}
