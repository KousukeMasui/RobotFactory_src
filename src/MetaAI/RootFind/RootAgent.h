#pragma once
#include"Object/Object.h"
#include<functional>
#include<vector>
#include"Model/Model/Model.h"
//�o�H�T���œ����x�[�X�N���X
//���ۂ̈ړ��̓I�u�W�F�N�g���ɈႤ�������s�������̂ł����ɏ����͏����Ȃ�
class RootAgent{
public:
	//�R���X�g���N�^
	explicit RootAgent(Object& object);
	//�f�X�g���N�^
	~RootAgent();

	//�X�V
	void Update(float deltaTime,float range);
	//���̌o�H�_�ւ̕����x�N�g����Ԃ�
	MyVector3 ToNextVelocity() const;
	//�I�u�W�F�N�g�����̌o�H�_�։�]������
	bool RotateToNext(float deltaTime);
	//�o�H�T���҂���
	bool IsFindWait() const;
	//�o�H�T�����ɂ���
	void StartFind();
	//�o�H��^����
	void SetRoot(const MyVector3& position);
	void SetRoot(const std::vector<MyVector3>& root);
	//�ʒu�|�C���^��Ԃ�
	MyVector3* Position();
	//�o�H�����݂��邩
	bool IsMove() const;
	//�ŏI���B�ڕW��Ԃ�
	const MyVector3 EndPoint() const;
	//�o�H�폜
	void Delete();
	//�o�H��`��
	void Draw(const Color& color) const;
private:
	//�o�H�T���ňړ�������I�u�W�F�N�g
	Object& m_object;
	//�o�H�ۑ��ϐ�
	std::vector<MyVector3> m_root;
	//�o�H�T���҂���
	bool m_isFindWait;
	//���̌o�H�_�ւ̕����x�N�g��
	MyVector3 m_toNextVelocity;
	//�o�H���f��
	Model m_rootModel;
};