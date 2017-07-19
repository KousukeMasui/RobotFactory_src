#pragma once

#include"../PriorityToFactory.h"
class PriorityReturnFactory : public PriorityToFactory
{
public:
	PriorityReturnFactory(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	PriorityReturnFactory(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units,UnitFactory& factory);
private:
	UnitPtrs GetUnits() override;
};