#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"UI/UI.h"
#include<vector>
#include<functional>
#include<memory>
//連続でアクションを行うアクション
class Link : public UIAction
{
public:
	Link(int actionSize, bool isLoop = false, ...);
	Link(std::vector<std::shared_ptr<UIAction>> actions,bool isLoop = false);
	~Link();
	virtual bool Update(UI* ui, float deltaTime) override;

private:
	std::vector<std::shared_ptr<UIAction>> m_actions;
	unsigned int m_actionSize;
	unsigned int m_actionIndex;
	bool m_isLoop;
};