#include "PriorityToPartsAction.h"
#include"Actor/Unit/Unit.h"
#include"Cursor\LerpCursor.h"
#include"World/World.h"
#include"Base/VectorUtility/VectorUtility.h"
PriorityToPartsAction::PriorityToPartsAction(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units):
	PriorityToLiftObject(priority,world,id,cursor,units)
{
}

PriorityToPartsAction::~PriorityToPartsAction()
{
}

bool PriorityToPartsAction::OnFind(const LiftObject & lift)
{
	//�p�[�c�Ŏ�����Ă��Ȃ�
	return !lift.IsLiftStart() && lift.GetID()==LIFT_ID::PARTS;
}
