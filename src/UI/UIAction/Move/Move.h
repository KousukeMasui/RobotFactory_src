#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"Math/Vector/MyVector2.h"
class UI;
class Move : public UIAction
{
public:
	Move(const MyVector2& begin, const MyVector2&  end, float totalFrame);
	~Move();

	virtual bool Update(UI* ui, float deltaTime) override;

private:
	MyVector2 m_begin;
	MyVector2 m_end;

	float m_totalFrame;

	float m_timer;

};