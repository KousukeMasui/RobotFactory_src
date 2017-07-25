#pragma once
#include<DxLib.h>
#include"../GamePad.h"
//�R���o�[�^�[���ƂɃ{�^���̔ԍ����قȂ�̂ŗv�m�F
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

	//�C���v�b�g�̍X�V
	void Update() override;

	//�X�e�B�b�N
	virtual MyVector2 GetLeftStick() const override;
	virtual MyVector2 GetRightStick() const override;

	//�{�^������
	virtual bool IsEnter(int buttonID) const override;
	virtual bool IsState(int buttonID) const override;
	virtual bool IsExit(int buttonID) const override;
private:

	//1�t���[���O�̓���
	DINPUT_JOYSTATE m_prevState;
	//���݂̓���
	DINPUT_JOYSTATE m_currentState;
};