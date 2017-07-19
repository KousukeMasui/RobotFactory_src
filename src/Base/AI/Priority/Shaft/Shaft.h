#pragma once

#include"../PriorityActionPtr.h"
#include<vector>
//��������f�ޗ������ɂ��Ďv�l������
//�ʒu�AHP�Ȃǂ���̎��Ő��l�Ƃ��ċ��߂����Ă���Ƃ��������̗D�揇�ʂƂŔ�r���Ĕ��f����
class Shaft
{
public:
	//�R���X�g���N�^
	Shaft();
	//�f�X�g���N�^
	~Shaft();
	void Initialize();
	//�X�V
	bool Update(float deltaTime);
	//�`��@�f�o�b�O�p
	void DebugDraw() const;
	//�s���ǉ�
	void Add(const PriorityActionPtr& action);
private:
	//�ł������ɓ������A�N�V�����̎擾
	void Change();
private:
	PriorityActionPtr m_nowAction;
	std::vector<PriorityActionPtr> m_actions;
};