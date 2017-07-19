#include "RangeOpenList.h"

//�R���X�g���N�^

RangeOpenList::RangeOpenList(float cost) :
	m_front(nullptr),
	m_cost(cost)
{

}

//�����J�n

void RangeOpenList::Start(const NodePtr & start)
{
	m_queue.Push(start);
}

//��?

bool RangeOpenList::IsEmpty() const
{
	return m_queue.IsEmpty();
}

//�m�[�h�̎擾

void RangeOpenList::Pop()
{
	m_front = m_queue.Pop();
}

//�擪�m�[�h�̎擾

NodePtr RangeOpenList::GetFront() const
{
	return m_front;
}

//�m�[�h�̒ǉ�

void RangeOpenList::Push(const NodePtr & node)
{
	if (node->IsOpened()) return;
	node->update(*m_front);
	if (node->Total() < m_cost)
	{
		m_queue.Push(node);
	}
}

bool RangeOpenList::IsGoal() const
{
	return m_front->IsTarget();
}
