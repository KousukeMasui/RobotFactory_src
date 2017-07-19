#pragma once
#include"../Node/Node/NodePtr.h"
#include"../Node/NodePriorityQueue/NodePriorityQueue.h"
class DijkstraOpenList
{
public:
	//�R���X�g���N�^
	DijkstraOpenList();

	//�����J�n
	void Start(const NodePtr& start);

	//��?
	bool IsEmpty();

	//�m�[�h�̎擾
	void Pop();

	//�擪�̃m�[�h���擾
	NodePtr GetFront() const;
	//�m�[�h�̒ǉ�
	void Push(const NodePtr& node);

	//�ړI�n�̃m�[�h�ɓ��B������
	bool IsGoal() const;



private:
	//�擪�̃m�[�h
	NodePtr			m_front;
	//�D�揇�ʕt���L���[
	NodePriorityQueue m_queue;
};