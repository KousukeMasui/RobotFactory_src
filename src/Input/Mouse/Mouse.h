#pragma once
#include"Math/Vector/MyVector2.h"
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Effect\MouseEffect.h"
#include<memory>
enum MouseCommand
{
	LEFT = 0,
	RIGHT,
	MIDDLE,
	MAX
};

class Mouse
{
private:
	Mouse() = default;
	~Mouse() = default;

public:
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	Mouse(Mouse&&) = delete;
	Mouse& operator=(Mouse&&) = delete;

	static Mouse& GetInstance()
	{
		static Mouse inst;
		return inst;
	}

	void Initialize();
	void Update(float deltaTime);

	void Draw() const;//�G�t�F�N�g�\��

	//���݂̃}�E�X�̈ʒu��Ԃ�
	MyVector2 Position() const;
	//�}�E�X��1�t���[��������̈ړ��ʂ�Ԃ�(���K���͂��Ă��܂���B)
	MyVector2 Velocity() const;
	float Wheel();



	//�}�E�X�̈ʒu���烉�C���𐶐�
	Line3D ToWorldLine();

	bool IsPressDown(MouseCommand command);
	bool IsPressDown(MouseCommand command,MyVector2* point);
	bool IsPressState(MouseCommand command);
	bool IsPressState(MouseCommand command, MyVector2* point);
	bool IsPressUp(MouseCommand command);
	bool IsPressUp(MouseCommand command,MyVector2* point);
private:
	bool isCurrentPress[3]; //���̃t���[���ɉ����ꂽ��true
	bool isPreviosPress[3]; //1�t���[���O�ɉ����ꂽ��true
	MouseEffect m_effect;
	//�}�E�X�̃C���v�b�g���
	int mouseInput;
	//�}�E�X�̈ړ���
	MyVector2 m_velocity;
	//�}�E�X�̍X�V�O�̈ʒu
	MyVector2 m_prevPosition;
};