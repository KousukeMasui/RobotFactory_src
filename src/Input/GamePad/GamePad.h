#pragma once

#include"Math/Vector/MyVector2.h"
#include"Math/Vector/MyVector3.h"
class GamePad
{
public:
	GamePad(int padID,const MyVector2& clamp);
	~GamePad();

	//スティック
	virtual MyVector2 GetLeftStick() const = 0;
	virtual MyVector2 GetRightStick() const = 0;
	//3D版
	MyVector3 GetLeftStick3D() const;
	MyVector3 GetRightStick3D() const;
	//ボタン押下
	virtual bool IsEnter(int buttonID) const = 0;
	virtual bool IsState(int buttonID) const = 0;
	virtual bool IsExit(int buttonID) const = 0;

	//更新
	virtual void Update() = 0;
	int PadID() const;
protected:
	//スティックの数値を0~1にする
	MyVector2 StickNormalize(const MyVector2& stick) const;
protected:
	//ゲームパッドの番号
	const int m_padID;
private:
	const MyVector2 m_stickClamp;
};