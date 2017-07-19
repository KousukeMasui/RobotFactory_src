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
	//ã‚Ì•¨‚Ù‚Ç—Dæ“x‚ª‚‚­‚È‚é
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
	//ˆê”Ôª‚Á‚±‚Ì‚à‚Ì‚È‚Ì‚Å•K‚¸‚±‚Ìnode‚É‚½‚Ç‚è’…‚­‚æ‚¤‚É–³ğŒ‚Åtrue
	return true;
}

void IdleNode::OnUpdate(float deltaTime)
{
	m_unit.RoadDelete();
}

bool IdleNode::SetIsEnd()
{
	return true;
}
