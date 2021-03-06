#pragma once
#include"../PriorityToFactory.h"
#include"Math/Vector/MyVector3.h"


class PriorityHealAction : public PriorityToFactory
{
public:
	PriorityHealAction(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor,float hpPer, UnitPtrs& units);
	~PriorityHealAction();

	//初期化
	void Initialize() override;
protected:
	bool IsDisablePriority(const UnitPtr& unit) const override;
	UnitPtrs GetUnits() override;
private:
	//検索する際のhpの%
	const float m_hpPer;
};