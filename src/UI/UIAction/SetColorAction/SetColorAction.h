#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"Math/Color/Color.h"
//�A���ŃA�N�V�������s���A�N�V����
class SetColorAction : public UIAction
{
public:
	SetColorAction(Color begin,Color end,float totalFrame);
	~SetColorAction();
	virtual bool Update(UI* ui, float deltaTime) override;

private:
	Color m_begin;
	Color m_end;

	float m_timer;
	float m_totalFrame;
};