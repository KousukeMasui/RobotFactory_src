#pragma once
#include"../PriorityToLiftObject.h"
class PriorityToDeadUnit : public PriorityToLiftObject
{
public:
	PriorityToDeadUnit(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	~PriorityToDeadUnit();

private:
	//目的とする持つオブジェクトの条件式
	bool OnFind(const LiftObject& lift) override;
};