#pragma once
#include"../PriorityToLiftObject.h"
class PriorityToDeadUnit : public PriorityToLiftObject
{
public:
	PriorityToDeadUnit(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	~PriorityToDeadUnit();

private:
	//�ړI�Ƃ��鎝�I�u�W�F�N�g�̏�����
	bool OnFind(const LiftObject& lift) override;
};