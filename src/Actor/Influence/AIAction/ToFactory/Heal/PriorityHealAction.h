#pragma once
#include"../PriorityToFactory.h"
#include"Math/Vector/MyVector3.h"


class PriorityHealAction : public PriorityToFactory
{
public:
	PriorityHealAction(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor,float hpPer, UnitPtrs& units);
	~PriorityHealAction();

	//������
	void Initialize() override;
protected:
	bool IsDisablePriority(const UnitPtr& unit) const override;
	UnitPtrs GetUnits() override;
private:
	//��������ۂ�hp��%
	const float m_hpPer;
};