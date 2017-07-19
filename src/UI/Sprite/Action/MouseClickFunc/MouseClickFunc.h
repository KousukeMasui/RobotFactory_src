#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"../../Sprite.h"
#include<functional>
//マウスでクリックした際の処理を行う関数
class MouseClickFunc : public SpriteAction
{
public:
	explicit MouseClickFunc(const std::function<void(Sprite* sprite)>& clickFunc);
	MouseClickFunc(const std::function<void(Sprite* sprite)>& clickFunc,
		const std::function<void(Sprite* sprite)>& nonClickFunc);
	~MouseClickFunc();

	virtual bool OnUpdate(Sprite* sprite, float deltaTime) override;

private:
	std::function<void(Sprite* sprite)> m_clickFunc;
	std::function<void(Sprite* sprite)> m_nonClickFunc;
};