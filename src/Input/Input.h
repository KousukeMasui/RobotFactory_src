#pragma once

#include<array>
#include<functional>
#include<DxLib.h>
#include"Math/MyMath.h"
#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"

enum class KeyAction {
	KeyBoadShutDown,
	GamePadShutDown,

	Max_Of_Num
};

class Input {
private:
	Input();
	~Input();

private:
	void RegistFunc();

public:
	static Input& GetInstance();
	void Update();
	void PadInitialize();

	/*　キーボード関係のキー入力　*/
	bool IsKeyBoadUp(int key);    //ゲームパッド UP
	bool IsKeyBoadDown(int key);  //ゲームパッド DOWN
	bool IsKeyBoadState(int key); //ゲームパッド STATE

	/*　ゲームパッド関係のキー入力　*/
	bool IsGamePadUp(int key);    //ゲームパッド UP
	bool IsGamePadDown(int key);  //ゲームパッド DOWN
	bool IsGamePadState(int key); //ゲームパッド STATE

	//移動量取得
	MyVector3 GetVelocity();
	MyVector2 GetStickAngle();
	void Draw();

	bool GetAction(KeyAction action);
private:
	static const int Max_Key_Num = 256;
	using Keys = std::array<char, Max_Key_Num>;

	/* キーボード関係 　*/
	Keys curKeys;   //キーの現在の押下状況保存
	Keys preKeys;   //キーの1F前の押下状況保存
	/* ゲームパッド関係 */
	XINPUT_STATE xInput;   //キーの現在の押下状況保存
	XINPUT_STATE XBState;   //キーの1F前の押下状況保存

	//スティックのステイト情報
	XINPUT_STATE stick;
	float xStick;
	float yStick;

	using ActionFunc = std::array < std::function<bool(void)>, static_cast<int>(KeyAction::Max_Of_Num)>;
	ActionFunc actionFunc;
};