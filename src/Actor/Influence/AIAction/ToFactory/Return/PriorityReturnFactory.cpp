#include "PriorityReturnFactory.h"
#include"Actor/Unit/Unit.h"
#include"Cursor/LerpCursor.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/Unit/Base/UnitAnimationID.h"
PriorityReturnFactory::PriorityReturnFactory(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units):
	PriorityToFactory(priority,world,id,cursor,units,false)//ここでは違うユニットが既に狙っていてもそこに向かうようにする
{
}
PriorityReturnFactory::PriorityReturnFactory(float priority, IWorld & world, InfluenceID id, 
	LerpCursor * cursor, UnitPtrs & units, UnitFactory & factory):
PriorityToFactory(priority, world, id, cursor, units, factory)
{
}
UnitPtrs PriorityReturnFactory::GetUnits()
{
	UnitPtrs result;
	for (auto unit : m_units)//条件を満たしていないユニットを除外
	{
		if (unit->GetLift() == nullptr) continue; //物を持っていないユニットは除外
		if (unit->IsMove()) continue;//移動中のユニットは除外
		if (!unit->GetLift()->IsLiftEnd()) continue;
		if (unit->GetModel().GetAnimationID() == (int)UnitAnimationID::LIFT_DOWN) continue;
		result.push_back(unit);
	}
	return result;
}
