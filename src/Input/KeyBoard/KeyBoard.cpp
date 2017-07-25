#include "KeyBoard.h"
#include<DxLib.h>
KeyBoard::KeyBoard()
{
	for (int index = 0; index < Max_Key_Num; ++index) {
		/*　キーボード配列の初期化　　*/
		curKeys[index] = 0;
		preKeys[index] = 0;
	}
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	for (int i = 0; i < Max_Key_Num; i++)
	{
		preKeys[i] = curKeys[i];
	}
	//現在のキーをcurKeysに入れてる
	GetHitKeyStateAll(curKeys);
}

bool KeyBoard::IsKeyBoadUp(int key) const
{
	return curKeys[key] == 0 && preKeys[key] == 1;
}

bool KeyBoard::IsKeyBoadDown(int key) const
{
	return curKeys[key] == 1 && preKeys[key] == 0;
}

bool KeyBoard::IsKeyBoadState(int key) const
{
	return curKeys[key] == 1 && preKeys[key] == 1;
}

MyVector3 KeyBoard::GetVelocity() const
{
	MyVector2 v2D = GetVelocity(KEY_INPUT_D, KEY_INPUT_A, KEY_INPUT_W, KEY_INPUT_S);



	//斜めの正規化
	if (v2D.Length() != 0.0f)
		v2D.Normalize();

	return MyVector3(v2D.x,0, v2D.y);
}

MyVector2 KeyBoard::GetArrowVelocity() const
{
	return GetVelocity(KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP, KEY_INPUT_DOWN).Normalize();
}

MyVector2 KeyBoard::GetVelocity(int leftID, int rightID, int upID, int downID) const
{
	MyVector2 result(0,0);
	if (curKeys[leftID]) result.x = -1.0f;
	else if (curKeys[rightID]) result.x = 1.0f;
	if (curKeys[upID]) result.y = -1.0f;
	else if (curKeys[downID]) result.y = 1.0f;
	return result;
}
