#include "PriorityToLiftObject.h"
#include"Actor/Unit/Unit.h"
#include"Cursor/LerpCursor.h"
#include"../Base/State/ToUnit/ToUnitState.h"
#include"../Base/CursorStateID.h"
#include"../Base/State/OrderLiftObject/OrderLiftObjectState.h"
#include"World/World.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
PriorityToLiftObject::PriorityToLiftObject(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units):
	GamePriorityAction(priority,world,id,cursor,units)
{
}

PriorityToLiftObject::~PriorityToLiftObject()
{
}

void PriorityToLiftObject::Initialize()
{
	m_isEnd = false;
	m_cursorManager.Add((int)CursorStateID::TO_UNIT, std::make_shared <ToUnitState>(m_cursor, m_orderUnit));
	m_cursorManager.Add((int)CursorStateID::TO_TARGET, std::make_shared<OrderLiftObjectState>(m_world, m_cursor, m_orderUnit, m_target));
	m_world.GetGameManager().GetMetaAI().Overlap().Add(&*m_target);
	m_cursorManager.SetState((int)CursorStateID::TO_UNIT);
}

void PriorityToLiftObject::Update(float deltaTime)
{
	if (m_orderUnit == nullptr || m_target == nullptr)
	{
		m_isEnd = true;
		return;
	}

	m_cursorManager.Update(deltaTime);
	m_isEnd = m_orderUnit->Agent().IsMove();
}

void PriorityToLiftObject::End()
{
	m_cursorManager.Initialize();
}

void PriorityToLiftObject::Draw() const
{
}

float PriorityToLiftObject::OnPriority()
{
	m_orderUnit = nullptr;
	m_target = nullptr;
	float min = FLT_MAX;

	for(auto unit : m_units)
	{
		//�ړ����A���邢�͕��������Ă��郆�j�b�g�����O
		if (unit->Agent().IsMove() || unit->GetLift() != nullptr || unit->GetParam().NodeID() ==(int)UnitNodeID::BATTLE) continue;

		//��ԋ߂����Ă�I�u�W�F�N�g���擾
		m_target = m_world.GetGameManager().GetMetaAI().Distance().GetNearLift(*unit, [&](const LiftObject& lift) {return Find(lift); });
		if (m_target == nullptr) continue;
		float toLift = m_world.GetGameManager().GetMetaAI().Distance().Distance(*unit,*m_target);
		//���j�b�g�܂ł̋���
		float toUnit = m_world.GetGameManager().GetMetaAI().Distance().Distance(*m_cursor, *unit);
		//����������ۑ�
		if (min >= toUnit + toLift)
		{
			min = toUnit + toLift;
			m_orderUnit = unit;
		}
	}
	return (m_distancePriority -min);
}

bool PriorityToLiftObject::Find(const LiftObject & lift)
{
	//���Ƀf�[�^�ɓ����Ă���ꍇfalse
	if (m_world.GetGameManager().GetMetaAI().Overlap().IsContains((void*)&lift)) return false;
	return OnFind(lift);
}
