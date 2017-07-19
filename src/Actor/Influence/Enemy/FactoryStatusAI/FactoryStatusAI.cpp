#include "FactoryStatusAI.h"
#include<DxLib.h>
FactoryStatusAI::FactoryStatusAI()
{
}
FactoryStatusAI::~FactoryStatusAI()
{
}
void FactoryStatusAI::SetPriority(const std::vector<FactoryStatusID>& priority)
{
	m_priority = priority;
}

void FactoryStatusAI::PowerUp(FactoryPtrs& factorys)
{
	for (auto factory : factorys)
	{
		PowerUp(factory);
	}
}

void FactoryStatusAI::PowerUp(FactoryPtr& factory)
{
	if (!factory->Status().IsStatusUp(FactoryStatusID::CREATE)) return;
	unsigned int length = m_priority.size();

	std::vector<int> percent;
	int total = 0;
	//Ç±ÇÍÇ≈frontÇ…ãﬂÇ¢íˆÅAämó¶Ç™çÇÇ≠Ç»ÇÈ
	for (unsigned int i = 0; i < length; i++)
	{
		percent.push_back(length - i);
		total += length - i;
	}

	int rand = GetRand(total - 1);
	int resultIndex = percent.size() - 1;
	for (unsigned int i = 0; i < percent.size(); i++)
	{
		rand -= percent[i];
		if (rand < 0)
		{
			resultIndex = i;
			break;
		}
	}
	factory->StatusUp(m_priority[resultIndex]);
}
