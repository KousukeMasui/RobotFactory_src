#pragma once
#include"../PriorityToLiftObject.h"
class PriorityToPartsAction : public PriorityToLiftObject
{
public:
	PriorityToPartsAction(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	~PriorityToPartsAction();
private:
	//�ړI�Ƃ��鎝�I�u�W�F�N�g�̏�����
	bool OnFind(const LiftObject& lift) override;
};