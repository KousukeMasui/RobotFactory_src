#include "SetColorAction.h"
#include"Math\MyMath.h"
#include"../../UI.h"
SetColorAction::SetColorAction(Color begin, Color end, float totalFrame):
	m_begin(begin),
	m_end(end),
	m_timer(0.0f),
	m_totalFrame(totalFrame)
{
}

SetColorAction::~SetColorAction()
{
}

bool SetColorAction::Update(UI* ui, float deltaTime)
{
	m_timer += deltaTime;

	if (m_timer >= m_totalFrame)
	{
		ui->SetColor(m_end);//F‚ðÝ’è
		m_timer = 0.0f;//‰Šú‰»
		return true;
	}

	ui->SetColor(MyMath::Lerp(m_begin, m_end, m_timer / m_totalFrame));

	return false;
}
