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
	return lift.GetID() == LIFT_ID::UNIT &&//���j�b�g
		!lift.IsLiftStart() && !((Unit&)lift).IsDead() &&//������Ă��Ȃ��A������ł��Ȃ�
		((Unit&)lift).NodeID() != (int)UnitNodeID::BATTLE &&//�퓬���łȂ�
		((Unit&)lift).GetInfluence() != m_influenceID && //�����̐��͂̃��j�b�g�łȂ�
		m_searchFunc((const UnitPtr&)lift);//�����̃����_
}
