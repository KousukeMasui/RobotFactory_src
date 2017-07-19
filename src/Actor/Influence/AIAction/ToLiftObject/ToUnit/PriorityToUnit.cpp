#include "PriorityToUnit.h"
#include"World/World.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
PriorityToUnit::PriorityToUnit(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units,const std::function<bool(const UnitPtr& unit)>& searchFunc):
	PriorityToLiftObject(priority,world,id,cursor,units),
	m_searchFunc(searchFunc)
{
}

PriorityToUnit::~PriorityToUnit()
{
}

bool PriorityToUnit::OnFind(const LiftObject & lift)
{
	return lift.GetID() == LIFT_ID::UNIT &&//ユニット
		!lift.IsLiftStart() && !((Unit&)lift).IsDead() &&//持たれていない、かつ死んでいない
		((Unit&)lift).NodeID() != (int)UnitNodeID::BATTLE &&//戦闘中でない
		((Unit&)lift).GetInfluence() != m_influenceID && //自分の勢力のユニットでない
		m_searchFunc((const UnitPtr&)lift);//引数のラムダ
}
