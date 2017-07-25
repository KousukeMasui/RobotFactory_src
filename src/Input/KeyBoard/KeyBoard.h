#pragma once
#include"Math/Vector/MyVector2.h"
#include"Math/Vector/MyVector3.h"
//キーボードクラス
class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();
	//更新
	void Update();
	/*　キーボード関係のキー入力　*/
	bool IsKeyBoadUp(int key) const;    //ゲームパッド UP
	bool IsKeyBoadDown(int key) const;  //ゲームパッド DOWN
	bool IsKeyBoadState(int key) const; //ゲームパッド STATE

	MyVector3 GetVelocity() const;
	MyVector2 GetArrowVelocity() const;
private:
	MyVector2 GetVelocity(int leftID, int rightID, int upID, int downID) const;
private:
	//キーボード判定に使う要素数
	static const int Max_Key_Num = 256;
	/* キーボード関係 　*/
	char curKeys[Max_Key_Num];   //キーの現在の押下状況保存
	char preKeys[Max_Key_Num];   //キーの1F前の押下状況保存
};