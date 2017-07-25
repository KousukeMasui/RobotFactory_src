#pragma once

#include<DxLib.h>
#include"../GamePad.h"

class XInput : public GamePad
{
public:
	explicit XInput(int padID);
	~XInput();

	//インプットの更新
	void Update() override;

	//スティック
	virtual MyVector2 GetLeftStick() const override;
	virtual MyVector2 GetRightStick() const override;

	//ボタン押下
	virtual bool IsEnter(int buttonID) const override;
	virtual bool IsState(int buttonID) const override;
	virtual bool IsExit(int buttonID) const override;
private:

	//1フレーム前の入力
	XINPUT_STATE m_prevState;
	//現在の入力
	XINPUT_STATE m_currentState;
};