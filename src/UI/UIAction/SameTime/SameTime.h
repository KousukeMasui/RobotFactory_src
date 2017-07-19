#pragma once

#include"UI/UIAction/Base/UIActions.h"
#include<vector>
#include<functional>
#include<memory>
class UI;

class SameTime : public UIAction
{
public:

	SameTime(int actionSize, ...);
	explicit SameTime(const std::vector<std::shared_ptr<UIAction>>& actions);
	~SameTime();

	virtual bool Update(UI* ui, float deltaTime);

private:
	std::vector<std::shared_ptr<UIAction>> m_actions;
};