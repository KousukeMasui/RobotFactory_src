#include "StateManager.h"

StateManager::StateManager():
	m_endFunc([]() {}),
	m_startFunc([]() {}),
	m_updateFunc([](float deltaTime) {return true; }),
	m_isTransition(false),
	m_isStart(true),
	m_nowState(-1)
{
}

StateManager::~StateManager()
{
}

void StateManager::Add(int ID, const std::shared_ptr<IState>& state)
{
	m_states[ID] = state;
}

void StateManager::Update(float deltaTime)
{
	if (!TransitionUpdate(deltaTime)) return;
	m_states[m_nowState]->Update(deltaTime);

	Change();
}

void StateManager::Initialize()
{
	m_states.clear();
}

bool StateManager::TransitionUpdate(float deltaTime)
{
	//�J�ڒ��ȊO��true
	if (!m_isTransition) return true;

	if (m_updateFunc(deltaTime))
	{
		if (m_isStart)
		{
			m_startFunc();
			//�I��������
			m_states[m_nowState]->End();
			//state�ύX
			m_nowState = m_states[m_nowState]->Next();
			//�V����state��������
			m_states[m_nowState]->Initialize();
			m_isStart = false;
		}
		else m_isTransition = false;
	}

	return false;
}

void StateManager::Draw() const
{
	m_states.at(m_nowState)->Draw();
}

void StateManager::SetState(int ID)
{
	m_nowState = ID;
	//�V����state��������
	m_states[m_nowState]->Initialize();
}

void StateManager::SetFunc(const std::function<void()>& endFunc, const std::function<void()>& startFunc, const std::function<bool(float deltaTime)>& updateFunc)
{
	m_endFunc = endFunc;
	m_startFunc = startFunc;
	m_updateFunc = updateFunc;
}

void StateManager::Change()
{
	//�I������ꍇ
	if (m_states[m_nowState]->IsEnd())
	{
		m_isTransition = true;
		m_isStart = true;
		m_endFunc();

		printf("�e�X�g");
	}
}
