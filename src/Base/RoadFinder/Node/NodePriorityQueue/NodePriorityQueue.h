#pragma once
#include"../Node/NodePtr.h"
#include "PriorityQueue.h"
//�m�[�h�p
class NodePriorityQueue
{
public:
	//�R���X�g���N�^
	NodePriorityQueue();
	//��?
	bool IsEmpty() const;
	//�m�[�h�̎擾
	NodePtr Pop();
	//�m�[�h�̒ǉ�
	void Push(const NodePtr& node);

	void Clear();
private:
	//�m�[�h�̔�r�֐�
	static bool Comp(const NodePtr& n1, const NodePtr& n2);
private:
	//�m�[�h��r�֐��^
	typedef bool(*CompNode)(const NodePtr&, const NodePtr&);
	//�D�揇�ʕt���L���[
	PriorityQueue<NodePtr, CompNode> m_queue;
};