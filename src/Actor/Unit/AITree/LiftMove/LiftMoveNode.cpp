#include "LiftMoveNode.h"
#include"../../Unit.h"
#include"Actor\LiftObject\LiftObject.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitAnimationID.h"
LiftMoveNode::LiftMoveNode(Unit& unit):
	UnitAINode(unit,UnitNodeID::LIFT_MOVE)
{
}

LiftMoveNode::~LiftMoveNode()
{
}

void LiftMoveNode::Start()
{
	m_unit.GetModel().ChangeAnimation(UnitAnimationID::WALK_CARRY, true);
	m_isEnd = true;
}

void LiftMoveNode::End()
{
}

bool LiftMoveNode::Branch()
{
	return m_unit.Agent().IsMove();
}

void LiftMoveNode::OnUpdate(float deltaTime)
{
	//ˆÚ“®

	m_unit.Agent().RotateToNext(deltaTime);

	m_unit.Move(m_unit.Agent().ToNextVelocity() * m_unit.GetStatus().Status(UNIT_STATUS_ID::SPD));

	m_unit.GetLift()->LiftUp(m_unit);
}

bool LiftMoveNode::SetIsEnd()
{
	return true;
}
