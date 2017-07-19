#pragma once

#include"UI/UIAction/Base/UIActions.h"
#include<vector>
#include"Math/MyRect/MyRect.h"
#include"Math/Vector/MyVector2.h"
class Sprite;
class Animation : public SpriteAction
{
public:
	Animation(int cellNum,const MyVector2& cellSize,float changeTime);
	Animation(float changeTime,int cellNum, ...);
	~Animation();

	virtual bool OnUpdate(Sprite* sprite, float deltaTime) override;

private:
	std::vector<MyRect> m_animationRect;
	int m_index;
	float m_timer;
	const float m_changeTime;
};