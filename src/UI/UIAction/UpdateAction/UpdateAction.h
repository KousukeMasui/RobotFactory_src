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
	//実行するかどうかの判定
	std::function<void(UI* ui)> m_Func;
};