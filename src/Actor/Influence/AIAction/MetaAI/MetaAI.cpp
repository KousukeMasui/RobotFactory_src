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
	//生きているユニットを全て取得
	auto units = m_manager->GetUnitManager().GetFunction([&](const Unit& u) {
		return !u.IsDead() && &u != &unit;
	});
	std::vector<Point2> result;
	for (auto u : units)
	{
		//移動中の場合
		if (u->Agent().IsMove())
		{
			//目的地を保存
			result.push_back(PathFind3DUtility::ToNodePoint2(u->Agent().EndPoint()));
		}
		else
		{
			//現在の位置を保存
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
