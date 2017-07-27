#include "OverlapData.h"

OverlapData::OverlapData()
{
}

OverlapData::~OverlapData()
{
}

void OverlapData::Add(void * data)
{
	if (data == nullptr) return;
	if(!IsContains(data))//���ɒǉ����Ă���ꍇ�ǉ����s��Ȃ�
		m_data.push_front(data);
}

void OverlapData::Remove(void * data)
{
	if (data == nullptr) return;
	m_data.remove(data);
}

bool OverlapData::IsContains(void * data)
{
	if (data == nullptr) return true;
	for (auto v : m_data)
	{
		if (v == data) return true;
	}
	return false;
}
