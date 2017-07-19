#pragma once
#include"UI/UIAction/Base/UIActions.h"
class Fade : public UIAction
{
public:
	Fade(float begin,float end,float totalFrame);
	~Fade();

	virtual bool Update(UI* ui,float deltaTime) override;

private:
	float m_begin;
	float m_end;

	float m_totalFrame;

	float m_timer;

};