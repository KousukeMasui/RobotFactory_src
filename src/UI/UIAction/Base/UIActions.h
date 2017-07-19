#pragma once

#include"BaseUIAction.h"

//UIクラスで使用するために継承関係を作る
//テンプレート引数が継承関係でもテンプレートは継承にならない
class UIAction : public BaseUIAction<UI>
{
public:
	UIAction() {};
};
class Sprite;
class SpriteAction : public UIAction {
public:
	SpriteAction() {};
	bool Update(UI* ui, float deltaTime) override{
		return OnUpdate((Sprite*)ui, deltaTime);
	}

	virtual bool OnUpdate(Sprite* sprite, float deltaTime) = 0;
};
//フォント用
class FontSprite;
class FontAction : public UIAction {
public:
	FontAction() {};
	bool Update(UI* ui, float deltaTime) override {
		return OnUpdate((FontSprite*)ui, deltaTime);
	}
	virtual bool OnUpdate(FontSprite* sprite, float deltaTime) = 0;
};