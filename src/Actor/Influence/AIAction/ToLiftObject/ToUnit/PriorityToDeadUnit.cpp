#include "PriorityToDeadUnit.h"
#include"World/World.h"
PriorityToDeadUnit::PriorityToDeadUnit(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units):
	PriorityToLiftObject(priority,world,id,cursor,units)
{
}

PriorityToDeadUnit::~PriorityToDeadUnit()
{
}

bool PriorityToDeadUnit::OnFind(const LiftObject & lift)
{
	//ユニットで死んでいる
	return lift.GetID() ==LIFT_ID::UNIT &&
		!lift.IsLiftStart() && ((Unit&)lift).IsDead();
}
