#include "DijkstraOpenList.h"

//�R���X�g���N�^

DijkstraOpenList::DijkstraOpenList() :
	m_front(nullptr)
{
}

//�����J�n

void DijkstraOpenList::Start(const NodePtr & start)
{
	m_queue.Push(start);
}

//��?

bool DijkstraOpenList::IsEmpty()
{
	return m_queue.IsEmpty();
}

//�m�[�h�̎擾

void DijkstraOpenList::Pop()
{
	m_front = m_queue.Pop();
}

//�擪�̃m�[�h���擾

NodePtr DijkstraOpenList::GetFront() const
{
	return m_front;
}

//�m�[�h�̒ǉ�

void DijkstraOpenList::Push(const NodePtr & node)
{
	if (!node->IsUpdate(*m_front)) return;
	node->update(*m_front);
	m_queue.Push(node);
}

//�ړI�n�̃m�[�h�ɓ��B������

bool DijkstraOpenList::IsGoal() const
{
	return m_front->IsTarget();
}
