#include "AstarOpenList.h"

//�R���X�g���N�^

AstarOpenList::AstarOpenList(const NodePtr & target) :
	m_front(nullptr),
	m_target(target)
{
}

//�����J�n

void AstarOpenList::Start(const NodePtr & start)
{
	m_queue.Push(start);
}

//��?

bool AstarOpenList::IsEmpty()
{
	return m_queue.IsEmpty();
}

//�m�[�h�̎擾

void AstarOpenList::Pop()
{
	m_front = m_queue.Pop();
}

//�擪�̃m�[�h���擾

NodePtr AstarOpenList::GetFront() const
{
	return m_front;
}

//�m�[�h�̒ǉ�

void AstarOpenList::Push(const NodePtr & node)
{
	if (!node->IsUpdate(*m_front)) return;
	node->update(*m_front, node->Distance(*m_target));
	m_queue.Push(node);
}

//�ړI�n�̃m�[�h�ɓ��B������

bool AstarOpenList::IsGoal() const
{
	return m_front == m_target;
}
