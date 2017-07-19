#include "Shaft.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"../PriorityAction.h"
Shaft::Shaft()
{
}

Shaft::~Shaft()
{
}

void Shaft::Initialize()
{
	Change();
}

bool Shaft::Update(float deltaTime)
{
	if (m_nowAction == nullptr)
	{
		Change();
		return false;
	}
	m_nowAction->Update(deltaTime);
	if (m_nowAction->IsEnd())
	{
		m_nowAction->End();
		Change();
	}
	return true;
}

void Shaft::DebugDraw() const
{
	m_nowAction->Draw();
}

void Shaft::Add(const PriorityActionPtr & action)
{
	m_actions.push_back(action);
}

void Shaft::Change()
{

	//�ł��D��l�������A�N�V�������擾
	m_nowAction =  VectorUtility::GetMostObject<PriorityActionPtr>(m_actions,
		[](const PriorityActionPtr& a1, const PriorityActionPtr& a2) 
	{ if (a1->Priority() >= a2->Priority()) return a1;
		return a2; });
	//��ԍ�������-�̏ꍇ�ǂ���s��Ȃ�
	if (m_nowAction->Priority() <= 0.0f)
	{
		m_nowAction = nullptr;
		return;
	}
	m_nowAction->Initialize();
}
