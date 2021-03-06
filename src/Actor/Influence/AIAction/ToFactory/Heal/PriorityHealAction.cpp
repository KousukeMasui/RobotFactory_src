#include "PriorityHealAction.h"
#include"World/World.h"
#include"Math/Collision/Collision3D.h"
#include"Cursor/LerpCursor.h"
#include"../../Base/CursorStateID.h"
#include"../../Base/State/ToUnit/ToUnitState.h"
#include"../../Base/State/OrderHeal/OrderHealState.h"
#include"Actor/UnitFactory/UnitFactory.h"
PriorityHealAction::PriorityHealAction(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor,float hpPer, UnitPtrs& units):
	PriorityToFactory(priority,world,id,cursor,units,false),
	m_hpPer(hpPer)
{
}

PriorityHealAction::~PriorityHealAction()
{
}

//初期化
void PriorityHealAction::Initialize()
{
	m_isEnd = false;
	if (m_orderUnit == nullptr || m_targetFactory == nullptr) return;
	m_cursorManager.Add((int)CursorStateID::TO_UNIT, std::make_shared <ToUnitState>(m_cursor, m_orderUnit));
	m_cursorManager.Add((int)CursorStateID::TO_TARGET, std::make_shared<OrderHealState>(m_world, m_cursor, m_orderUnit, m_targetFactory));
	m_cursorManager.SetState((int)CursorStateID::TO_UNIT);
}
bool PriorityHealAction::IsDisablePriority(const UnitPtr & unit) const
{
	return unit->GetSphere().IsCollide(m_targetFactory->GetHeal().GetSphere());
}
UnitPtrs PriorityHealAction::GetUnits()
{
	UnitPtrs result;
	for (auto unit : m_units)
	{
		//既に回復中の場合含めない
		auto factorys = m_world.GetGameManager().GetFactoryManager().GetVector(m_influenceID);
		for (auto factory : factorys)
			if (unit->GetSphere().IsCollide(factory->GetHeal().GetSphere())) continue;
		if (unit->GetStatus().hpPercent() <= m_hpPer &&//一定HP以下
			!unit->Agent().IsMove())//移動中でない
			result.push_back(unit);
	}
	return result;
}