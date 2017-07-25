#pragma once
#include"Math/Vector/MyVector2.h"
#include"Math/Vector/MyVector3.h"
//�L�[�{�[�h�N���X
class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();
	//�X�V
	void Update();
	/*�@�L�[�{�[�h�֌W�̃L�[���́@*/
	bool IsKeyBoadUp(int key) const;    //�Q�[���p�b�h UP
	bool IsKeyBoadDown(int key) const;  //�Q�[���p�b�h DOWN
	bool IsKeyBoadState(int key) const; //�Q�[���p�b�h STATE

	MyVector3 GetVelocity() const;
	MyVector2 GetArrowVelocity() const;
private:
	MyVector2 GetVelocity(int leftID, int rightID, int upID, int downID) const;
private:
	//�L�[�{�[�h����Ɏg���v�f��
	static const int Max_Key_Num = 256;
	/* �L�[�{�[�h�֌W �@*/
	char curKeys[Max_Key_Num];   //�L�[�̌��݂̉����󋵕ۑ�
	char preKeys[Max_Key_Num];   //�L�[��1F�O�̉����󋵕ۑ�
};