#pragma once
#include"../PriorityToLiftObject.h"
class PriorityToPartsAction : public PriorityToLiftObject
{
public:
	PriorityToPartsAction(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	~PriorityToPartsAction();
private:
	//目的とする持つオブジェクトの条件式
	bool OnFind(const LiftObject& lift) override;
};