#include "PriorityToFactory.h"
#include"World/World.h"
#include"../Base/CursorStateID.h"
#include"../Base/State/ToUnit/ToUnitState.h"
#include"../Base/State/OrderFactory/OrderFactoryState.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Actor/UnitFactory/UnitFactory.h"
PriorityToFactory::PriorityToFactory(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs& units, bool isContainsCheck):
	GamePriorityAction(priority,world,id,cursor,units),
	m_targetFactory(nullptr),
	m_isFactorySearch(true),
	m_isContainsCheck(isContainsCheck)
{
}

PriorityToFactory::PriorityToFactory(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units, UnitFactory & target) :
	GamePriorityAction(priority, world, id, cursor, units),
	m_targetFactory(&target),
	m_isFactorySearch(false),
	m_isContainsCheck(false)
{
}

void PriorityToFactory::Initialize()
{
	m_isEnd = false;
	m_cursorManager.Add((int)CursorStateID::TO_UNIT, std::make_shared <ToUnitState>(m_cursor, m_orderUnit));
	m_cursorManager.Add((int)CursorStateID::TO_TARGET, std::make_shared<OrderFactoryState>(m_world, m_cursor, m_orderUnit, m_targetFactory, m_influenceID));

	m_cursorManager.SetState((int)CursorStateID::TO_UNIT);

	m_world.GetMetaAI().Overlap().Add(&*m_targetFactory);
}

void PriorityToFactory::Update(float deltaTime)
{
	if (m_orderUnit == nullptr || m_targetFactory == nullptr)
	{
		m_isEnd = true;
		return;
	}
	m_cursorManager.Update(deltaTime);
	m_isEnd = m_orderUnit->IsMove();
}

void PriorityToFactory::End()
{
	if(m_isFactorySearch) m_targetFactory = nullptr;
	m_cursorManager.Initialize();
	//m_world.GetMetaAI().Overlap().Remove(&*m_targetFactory);
}

void PriorityToFactory::Draw() const
{
}

float PriorityToFactory::OnPriority()
{
	UnitPtrs units = GetUnits();
	if (units.empty()) return -1.0f;
	m_orderUnit = VectorUtility::GetMostObject<UnitPtr>(units, [&](const UnitPtr& u1, const UnitPtr& u2)
	{
		float d1,d2;
		if (m_isFactorySearch)
		{
			d1 = NearFactoryDistance(u1);
			if (IsDisablePriority(u1)) return u2;
			d2 = NearFactoryDistance(u2);
			if (IsDisablePriority(u2)) return u1;
		}
		else
		{
			d1 = NearFactoryDistance(u1, m_targetFactory);
			if (IsDisablePriority(u1)) return u2;
			d2 = NearFactoryDistance(u2, m_targetFactory);
			if (IsDisablePriority(u2)) return u1;
		}
		
		if (m_world.GetMetaAI().Distance().Distance(*m_cursor, *u1) + d1 <=
			m_world.GetMetaAI().Distance().Distance(*m_cursor, *u2) + d2)
			return u1;
		return u2;
	});
	if (m_targetFactory == nullptr) return -1.0f;//目的とする工場が見つからない場合
	if (m_orderUnit == nullptr || IsDisablePriority(m_orderUnit)) return -1.0f;
	
	//ユニットまでの距離 + 工場までの距離
	return m_distancePriority - (m_world.GetMetaAI().Distance().Distance(*m_orderUnit, m_targetFactory) +
		m_world.GetMetaAI().Distance().Distance(*m_cursor, *m_orderUnit));
}

UnitPtrs PriorityToFactory::GetUnits()
{
	m_isContainsCheck = true;
	//動いていないユニットを取得
	UnitPtrs result;
	for(auto unit : m_units)
	{
		if (!unit->IsMove())
			result.push_back(unit);
	}
	return result;
}

float PriorityToFactory::NearFactoryDistance(const UnitPtr & unit, UnitFactory * factory)
{
	auto factorys = m_world.GetGameManager().GetFactoryManager().All();
	HitInfo hit;
	Capsule capsule(unit->Position(), factory->GetParam().Position(), unit->GetSphere().m_radius);
	for (auto colFactory : factorys)//違う工場とぶつかる場合、一番近くではないので
	{
		if (&*colFactory == factory) continue;
		if (colFactory->IsCollide(capsule)) return -1.0f;
	}
	hit = factory->IsCollide(capsule.m_line);

	return MyVector3::Distance(hit.hitPosition, unit->Position());
}

float PriorityToFactory::NearFactoryDistance(const UnitPtr & unit)
{
	float min = FLT_MAX;
	auto myFactorys = m_world.GetGameManager().GetFactoryManager().GetVector(m_influenceID);
	clsDx();
	for (int i = 0; i < myFactorys.size();i++)
	//for (auto factory : myFactorys)
	{
		//既に誰かが狙っている場合false
		if (m_isContainsCheck && m_world.GetMetaAI().Overlap().IsContains(&*myFactorys[i])) continue;
		float distance = m_world.GetMetaAI().Distance().Distance(*unit, &*myFactorys[i]);
		if (min >= distance)
		{
			min = distance;
			m_targetFactory = &*myFactorys[i];
		}
	}
	return min;
}
