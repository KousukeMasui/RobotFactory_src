#include "IdleNode.h"

#include"Actor\Unit\AITree\Move\MoveNode.h"
#include"../Battle/BattleNode.h"
#include"../Dead/DeadNode.h"
#include"../LiftUp/LiftUpNode.h"
#include"../LiftIdle/LiftIdleNode.h"
#include"Actor\Unit\Unit.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitAnimationID.h"
IdleNode::IdleNode(IWorld & world, Unit& unit):
	UnitAINode(unit,UnitNodeID::IDLE)
{
	//上の物ほど優先度が高くなる
	AddChild(std::make_shared<DeadNode>(world, unit));
	AddChild(std::make_shared<LiftIdleNode>(world, unit));
	AddChild(std::make_shared<MoveNode>(unit));
	AddChild(std::make_shared<BattleNode>(world, unit));
	AddChild(std::make_shared<LiftUpNode>(world, unit));
	m_isEnd = true;
}

IdleNode::~IdleNode()
{
}

void IdleNode::Start()
{
	m_unit.GetModel().ChangeAnimation((int)UnitAnimationID::IDLE, true);
}
void IdleNode::End()
{
}

bool IdleNode::Branch()
{
	//一番根っこのものなので必ずこのnodeにたどり着くように無条件でtrue
	return true;
}

void IdleNode::OnUpdate(float deltaTime)
{
	m_unit.Agent().Delete();
}

bool IdleNode::SetIsEnd()
{
	return true;
}
