#include "NodePriorityQueue.h"

NodePriorityQueue::NodePriorityQueue():
	m_queue(Comp)
{
}

bool NodePriorityQueue::IsEmpty() const
{
	return m_queue.IsEmpty();
}

NodePtr NodePriorityQueue::Pop()
{
	auto node = m_queue.Pop();
	node->close();
	return node;
}

void NodePriorityQueue::Push(const NodePtr & node)
{
	if (node->IsOpened())
	{
		m_queue.Update();
		return;
	}
	node->Open();
	m_queue.Push(node);
}

void NodePriorityQueue::Clear()
{
	m_queue.Clear();
}

bool NodePriorityQueue::Comp(const NodePtr & n1, const NodePtr & n2)
{
	return  *n2 < *n1;
}
