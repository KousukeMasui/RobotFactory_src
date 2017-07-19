#pragma once
#include"../PriorityToLiftObject.h"
#include<functional>
class PriorityToUnit : public PriorityToLiftObject
{
public:
	PriorityToUnit(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units, const std::function<bool(const UnitPtr& unit)>& searchFunc);
	~PriorityToUnit();

private:
	//�ړI�Ƃ��鎝�I�u�W�F�N�g�̏�����
	bool OnFind(const LiftObject& lift) override;
private:
	const std::function<bool(const UnitPtr& unit)> m_searchFunc;
};