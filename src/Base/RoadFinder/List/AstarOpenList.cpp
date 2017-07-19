#include "AstarOpenList.h"

//コンストラクタ

AstarOpenList::AstarOpenList(const NodePtr & target) :
	m_front(nullptr),
	m_target(target)
{
}

//検索開始

void AstarOpenList::Start(const NodePtr & start)
{
	m_queue.Push(start);
}

//空か?

bool AstarOpenList::IsEmpty()
{
	return m_queue.IsEmpty();
}

//ノードの取得

void AstarOpenList::Pop()
{
	m_front = m_queue.Pop();
}

//先頭のノードを取得

NodePtr AstarOpenList::GetFront() const
{
	return m_front;
}

//ノードの追加

void AstarOpenList::Push(const NodePtr & node)
{
	if (!node->IsUpdate(*m_front)) return;
	node->update(*m_front, node->Distance(*m_target));
	m_queue.Push(node);
}

//目的地のノードに到達したか

bool AstarOpenList::IsGoal() const
{
	return m_front == m_target;
}
