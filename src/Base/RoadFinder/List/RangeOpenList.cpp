#include "RangeOpenList.h"

//コンストラクタ

RangeOpenList::RangeOpenList(float cost) :
	m_front(nullptr),
	m_cost(cost)
{

}

//検索開始

void RangeOpenList::Start(const NodePtr & start)
{
	m_queue.Push(start);
}

//空か?

bool RangeOpenList::IsEmpty() const
{
	return m_queue.IsEmpty();
}

//ノードの取得

void RangeOpenList::Pop()
{
	m_front = m_queue.Pop();
}

//先頭ノードの取得

NodePtr RangeOpenList::GetFront() const
{
	return m_front;
}

//ノードの追加

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
