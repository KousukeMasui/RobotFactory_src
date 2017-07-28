#include "Shaft.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"../PriorityAction.h"
Shaft::Shaft():
	m_changeFunc([]() {})
{
}

Shaft::~Shaft()
{
}

void Shaft::SetChangeFunc(const std::function<void()>& changeFunc)
{
	m_changeFunc = changeFunc;
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
		m_changeFunc();
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
	float resultPriority;
	//最も優先値が高いアクションを取得
	m_nowAction =  VectorUtility::GetMostObject<PriorityActionPtr>(m_actions,
		[&](const PriorityActionPtr& a1, const PriorityActionPtr& a2) 
	{ 
		float a1Priority = a1->Priority();
		float a2Priority = a2->Priority();
		if (a1Priority < 0 || a2Priority > a1Priority) {//a1が-、あるいはa2がa1より大きい場合
			resultPriority = a2Priority;
			return a2;
		}
		else {
			resultPriority = a1Priority;
			return a1;
		}
	});
	//一番高い物が-の場合どれも行わない
	if (resultPriority <= 0.0f)
	{
		m_nowAction = nullptr;
		return;
	}
	m_nowAction->Initialize();
}
