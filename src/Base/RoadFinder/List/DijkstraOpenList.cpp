#include "DijkstraOpenList.h"

//コンストラクタ

DijkstraOpenList::DijkstraOpenList() :
	m_front(nullptr)
{
}

//検索開始

void DijkstraOpenList::Start(const NodePtr & start)
{
	m_queue.Push(start);
}

//空か?

bool DijkstraOpenList::IsEmpty()
{
	return m_queue.IsEmpty();
}

//ノードの取得

void DijkstraOpenList::Pop()
{
	m_front = m_queue.Pop();
}

//先頭のノードを取得

NodePtr DijkstraOpenList::GetFront() const
{
	return m_front;
}

//ノードの追加

void DijkstraOpenList::Push(const NodePtr & node)
{
	if (!node->IsUpdate(*m_front)) return;
	node->update(*m_front);
	m_queue.Push(node);
}

//目的地のノードに到達したか

bool DijkstraOpenList::IsGoal() const
{
	return m_front->IsTarget();
}
