#pragma once
#include"../Node/Node/NodePtr.h"
#include"../Node/NodePriorityQueue/NodePriorityQueue.h"
//�͈͌����I�[�v�����X�g
class RangeOpenList
{
public:
	//�R���X�g���N�^
	explicit RangeOpenList(float cost);
	//�����J�n
	void Start(const NodePtr& start);
	//��?
	bool IsEmpty() const;

	//�m�[�h�̎擾
	void Pop();
	//�擪�m�[�h�̎擾
	NodePtr GetFront() const;

	//�m�[�h�̒ǉ�
	void Push(const NodePtr& node);

	bool IsGoal() const;

private:
	NodePtr				m_front;
	//�ړ��R�X�g
	float				m_cost;
	//�D�揇�ʕt���L���[
	NodePriorityQueue	m_queue;
};