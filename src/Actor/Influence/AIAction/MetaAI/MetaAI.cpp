#include "MetaAI.h"
#include"Manager/GameManager.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
MetaAI::MetaAI():
	m_manager(nullptr)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Start(GameManager* manager)
{
	m_manager = manager;
	m_distance.Start(manager);
}

void MetaAI::Update()
{
	m_distance.Clear();
	m_rootFind.Update();
}

std::vector<Point2> MetaAI::GetUnitPoints(const Unit & unit)
{
	//�����Ă��郆�j�b�g��S�Ď擾
	auto units = m_manager->GetUnitManager().GetFunction([&](const Unit& u) {
		return !u.IsDead() && &u != &unit;
	});
	std::vector<Point2> result;
	for (auto u : units)
	{
		//�ړ����̏ꍇ
		if (u->Agent().IsMove())
		{
			//�ړI�n��ۑ�
			result.push_back(PathFind3DUtility::ToNodePoint2(u->Agent().EndPoint()));
		}
		else
		{
			//���݂̈ʒu��ۑ�
			result.push_back(PathFind3DUtility::ToNodePoint2(u->Position()));
		}
	}
	return result;
}

MetaDistance & MetaAI::Distance()
{
	return m_distance;
}

OverlapData & MetaAI::Overlap()
{
	return m_overlap;
}

RootFind & MetaAI::GetFind()
{
	return m_rootFind;
}
