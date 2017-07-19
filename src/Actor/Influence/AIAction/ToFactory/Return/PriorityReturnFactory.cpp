#include "PriorityReturnFactory.h"
#include"Actor/Unit/Unit.h"
#include"Cursor/LerpCursor.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/Unit/Base/UnitAnimationID.h"
PriorityReturnFactory::PriorityReturnFactory(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units):
	PriorityToFactory(priority,world,id,cursor,units,false)//�����ł͈Ⴄ���j�b�g�����ɑ_���Ă��Ă������Ɍ������悤�ɂ���
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
	for (auto unit : m_units)//�����𖞂����Ă��Ȃ����j�b�g�����O
	{
		if (unit->GetLift() == nullptr) continue; //���������Ă��Ȃ����j�b�g�͏��O
		if (unit->IsMove()) continue;//�ړ����̃��j�b�g�͏��O
		if (!unit->GetLift()->IsLiftEnd()) continue;
		if (unit->GetModel().GetAnimationID() == (int)UnitAnimationID::LIFT_DOWN) continue;
		result.push_back(unit);
	}
	return result;
}
