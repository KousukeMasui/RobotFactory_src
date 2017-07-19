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
	//終了時に行う遷移処理
	std::function<void()> m_endFunc;
	std::function<void()> m_startFunc;
	//遷移が終わったかを確認する更新処理
	std::function<bool(float deltaTime)> m_updateFunc;
	//遷移中か
	bool m_isTransition;
	bool m_isStart;
	int m_nowState;
};