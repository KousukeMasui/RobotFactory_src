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

	/*�@�L�[�{�[�h�֌W�̃L�[���́@*/
	bool IsKeyBoadUp(int key);    //�Q�[���p�b�h UP
	bool IsKeyBoadDown(int key);  //�Q�[���p�b�h DOWN
	bool IsKeyBoadState(int key); //�Q�[���p�b�h STATE

	/*�@�Q�[���p�b�h�֌W�̃L�[���́@*/
	bool IsGamePadUp(int key);    //�Q�[���p�b�h UP
	bool IsGamePadDown(int key);  //�Q�[���p�b�h DOWN
	bool IsGamePadState(int key); //�Q�[���p�b�h STATE

	//�ړ��ʎ擾
	MyVector3 GetVelocity();
	MyVector2 GetStickAngle();
	void Draw();

	bool GetAction(KeyAction action);
private:
	static const int Max_Key_Num = 256;
	using Keys = std::array<char, Max_Key_Num>;

	/* �L�[�{�[�h�֌W �@*/
	Keys curKeys;   //�L�[�̌��݂̉����󋵕ۑ�
	Keys preKeys;   //�L�[��1F�O�̉����󋵕ۑ�
	/* �Q�[���p�b�h�֌W */
	XINPUT_STATE xInput;   //�L�[�̌��݂̉����󋵕ۑ�
	XINPUT_STATE XBState;   //�L�[��1F�O�̉����󋵕ۑ�

	//�X�e�B�b�N�̃X�e�C�g���
	XINPUT_STATE stick;
	float xStick;
	float yStick;

	using ActionFunc = std::array < std::function<bool(void)>, static_cast<int>(KeyAction::Max_Of_Num)>;
	ActionFunc actionFunc;
};