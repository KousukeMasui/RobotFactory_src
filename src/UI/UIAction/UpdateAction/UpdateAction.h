#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include<functional>
class UI;
class UpdateAction : public UIAction
{
public:
	explicit UpdateAction(const std::function<void(UI* ui)>& func);
	~UpdateAction();

	virtual bool Update(UI* ui, float deltaTime) override;

private:
	//���s���邩�ǂ����̔���
	std::function<void(UI* ui)> m_Func;
};