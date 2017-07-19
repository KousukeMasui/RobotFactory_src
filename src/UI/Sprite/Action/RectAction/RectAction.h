#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"Math/MyRect/MyRect.h"
class Sprite;
//連続でアクションを行うアクション
class RectAction : public SpriteAction
{
public:
	RectAction(MyRect begin, MyRect end, float totalFrame);
	~RectAction();
	virtual bool OnUpdate(Sprite* sprite, float deltaTime) override;

private:
	MyRect m_begin;
	MyRect m_end;

	float m_timer;
	float m_totalFrame;
};