#pragma once
#include "Math/Point2/Point2.h"
#include <functional>

// �����m�[�h
class Node
{
public:
	// �R���X�g���N�^
	Node(const Point2& position, int index);
	int Index();
	// ���W�̎擾
	Point2 position() const;

	//���v�R�X�g�̎擾
	float Total() const;

	// �X�V����
	void update(Node& parent, float h = 0.0f);

	//�������ɂ���
	void Open();
	//�������m�[�h��
	bool IsOpened();

	bool IsTarget() const;

	void TargetSet();
	// �����I���m�[�h���H
	bool closed() const;

	// �ړ��\���H
	bool walkable() const;

	// �����I���ɂ���
	void close();
	//�ړ��\���ݒ肷��
	void SetWalkable(bool isWalkable);

	bool IsUpdate(const Node& parent) const;

	// �ړI�n����X�^�[�g�n�_�܂ł����̂ڂ�
	void backtrack(std::function<void(Node& node)> f);

	float Distance(const Node& target) const;

	//��r�֐�
	bool operator < (const Node& other) const;

	// �����񉻁i�f�o�b�O�p�j
	std::string to_string() const;

private:
	Point2		m_position;		// ���W
	bool		m_isWalk;		// �ړ����Ă��邩�H
	float		m_cost;
	Node*		m_parent;		// �e���W
	bool		m_isOpened;
	bool		m_isClose;		// �������I�����Ă��邩�H
	bool		m_isTarget;		//�ڕW�n�_���H
	float		m_totalCost;
	float		m_estimate;//�S�[���܂ł̌��ς���
	bool		m_isPath;			// �p�X���̃m�[�h���H�i�f�o�b�O�p�j
	int m_index;
};


