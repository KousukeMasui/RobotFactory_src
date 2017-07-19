#pragma once

#include"BaseUIAction.h"

//UI�N���X�Ŏg�p���邽�߂Ɍp���֌W�����
//�e���v���[�g�������p���֌W�ł��e���v���[�g�͌p���ɂȂ�Ȃ�
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
//�t�H���g�p
class FontSprite;
class FontAction : public UIAction {
public:
	FontAction() {};
	bool Update(UI* ui, float deltaTime) override {
		return OnUpdate((FontSprite*)ui, deltaTime);
	}
	virtual bool OnUpdate(FontSprite* sprite, float deltaTime) = 0;
};