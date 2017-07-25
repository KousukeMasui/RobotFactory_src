#include "MoveNode.h"
#include"../../Unit.h"
#include"../Node/UnitNodeID.h"
#include"../../Unit.h"
#include"../../Base/UnitAnimationID.h"
MoveNode::MoveNode(Unit & unit):
	UnitAINode(unit,UnitNodeID::MOVE)
{
}

MoveNode::~MoveNode()
{
}

void MoveNode::Start()
{
	m_unit.GetParam().GetModel().ChangeAnimation(UnitAnimationID::WALK, true);
}
void MoveNode::End()
{
}

bool MoveNode::Branch()
{
	//à⁄ìÆâ¬î\ÅAÇ©Ç¬ìπÇ™ìoò^Ç≥ÇÍÇƒÇ¢ÇΩÇÁ
	return m_unit.GetLift() == nullptr &&
		m_unit.GetModel().GetAnimationID()!= UnitAnimationID::LIFT_UP &&
		(m_unit.Agent().IsMove());
}

void MoveNode::OnUpdate(float deltaTime)
{
	m_unit.Agent().RotateToNext(deltaTime);
	m_unit.Move(m_unit.Agent().ToNextVelocity() * m_unit.GetStatus().Status(UNIT_STATUS_ID::SPD));
}

bool MoveNode::SetIsEnd()
{
	return true;
}
