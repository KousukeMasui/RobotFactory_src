#pragma once

#include<DxLib.h>
#include"../GamePad.h"

class XInput : public GamePad
{
public:
	explicit XInput(int padID);
	~XInput();

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
	XINPUT_STATE m_prevState;
	//���݂̓���
	XINPUT_STATE m_currentState;
};