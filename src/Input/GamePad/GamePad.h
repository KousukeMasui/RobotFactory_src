#pragma once

#include"Math/Vector/MyVector2.h"
#include"Math/Vector/MyVector3.h"
class GamePad
{
public:
	GamePad(int padID,const MyVector2& clamp);
	~GamePad();

	//�X�e�B�b�N
	virtual MyVector2 GetLeftStick() const = 0;
	virtual MyVector2 GetRightStick() const = 0;
	//3D��
	MyVector3 GetLeftStick3D() const;
	MyVector3 GetRightStick3D() const;
	//�{�^������
	virtual bool IsEnter(int buttonID) const = 0;
	virtual bool IsState(int buttonID) const = 0;
	virtual bool IsExit(int buttonID) const = 0;

	//�X�V
	virtual void Update() = 0;
	int PadID() const;
protected:
	//�X�e�B�b�N�̐��l��0~1�ɂ���
	MyVector2 StickNormalize(const MyVector2& stick) const;
protected:
	//�Q�[���p�b�h�̔ԍ�
	const int m_padID;
private:
	const MyVector2 m_stickClamp;
};