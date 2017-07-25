#include "LiftIdleNode.h"
#include"Actor/LiftObject/LiftObject.h"
#include"Actor\Unit\AITree\LiftMove\LiftMoveNode.h"
#include"Actor\Unit\AITree\LiftDown\LiftDownNode.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitAnimationID.h"
#include"../../Unit.h"
LiftIdleNode::LiftIdleNode(IWorld & world, Unit& unit):
	UnitAINode(unit,UnitNodeID::LIFT_IDLE),
	m_world(world)
{
	AddChild(std::make_shared<LiftMoveNode>(unit));
	AddChild(std::make_shared<LiftDownNode>(world, unit));
	m_isEnd = true;
}

LiftIdleNode::~LiftIdleNode()
{
}

void LiftIdleNode::Start()
{
	//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“
	m_unit.GetModel().ChangeAnimation(UnitAnimationID::LIFT_IDLE, true);
}

void LiftIdleNode::End()
{
}

bool LiftIdleNode::Branch()
{
	//•¨‚ðŽ‚Á‚½ê‡
	return m_unit.GetLift() != nullptr&& m_unit.GetLift()->IsLiftEnd();
}

void LiftIdleNode::OnUpdate(float deltaTime)
{
	m_unit.Agent().Delete();
	m_unit.GetLift()->LiftUp(m_unit);
}

bool LiftIdleNode::SetIsEnd()
{
	return true;
}
