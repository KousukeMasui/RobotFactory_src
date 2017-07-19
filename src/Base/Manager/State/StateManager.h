#pragma once
#include<map>
#include<memory>
#include<functional>
#include"IState.h"
class StateManager
{
public:
	StateManager();
	~StateManager();

	void Add(int ID,const std::shared_ptr<IState>& state);
	void Update(float deltaTime);
	void Initialize();
	bool TransitionUpdate(float deltaTime);

	void Draw() const;
	void SetState(int ID);

	void SetFunc(const std::function<void()>& endFunc, const std::function<void()>& startFunc, 
					const std::function<bool(float deltaTime)>& updateFunc);
private:
	void Change();
private:
	std::map<int,std::shared_ptr<IState>> m_states;
	//�I�����ɍs���J�ڏ���
	std::function<void()> m_endFunc;
	std::function<void()> m_startFunc;
	//�J�ڂ��I����������m�F����X�V����
	std::function<bool(float deltaTime)> m_updateFunc;
	//�J�ڒ���
	bool m_isTransition;
	bool m_isStart;
	int m_nowState;
};