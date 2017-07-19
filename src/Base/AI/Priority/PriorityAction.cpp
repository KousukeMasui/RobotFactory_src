#include "PriorityAction.h"
#include<float.h>
PriorityAction::PriorityAction(float priority):
	m_priority(priority),
	m_isEnd(false)
{
}

bool PriorityAction::IsEnd() const
{
	return m_isEnd;
}

float PriorityAction::Priority()
{
	return m_priority * OnPriority();
}
