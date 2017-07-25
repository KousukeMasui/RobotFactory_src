#pragma once
#include<DxLib.h>
#include"../GamePad.h"
//コンバーターごとにボタンの番号が異なるので要確認
enum JC_PS101USV_ID
{
	TRIANGLE = 0,
	CIRCLE,
	CROSS,
	SQUEARE,
	L2,
	R2,
	L1,
	R1,
	START,
	SELECT,
	L3,
	R3
};

class DirectInput : public GamePad
{
public:
	explicit DirectInput(int padID);
	~DirectInput();

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
	DINPUT_JOYSTATE m_prevState;
	//現在の入力
	DINPUT_JOYSTATE m_currentState;
};