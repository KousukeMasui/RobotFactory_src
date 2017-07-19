#include "DeadNode.h"
#include"Actor\Base\IWorld.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitAnimationID.h"
#include"../../Base/UnitMessageID.h"
#include"UI/Sprite/BillBoard/Manager/BillBoardManager.h"
#include"UI/Sprite/BillBoard/BillBoard.h"
DeadNode::DeadNode(IWorld& world, Unit & unit):
	UnitAINode(unit,UnitNodeID::DEAD),
	m_world(world)
{
}

DeadNode::~DeadNode()
{
}

void DeadNode::Start()
{
	m_isEnd = false;
	m_unit.GetModel().ChangeAnimation((int)UnitAnimationID::DEAD, false);

	//‚Á‚Ä‚¢‚é•¨‚ª‚ ‚éê‡A‚»‚ê‚ğ‹ß‚­‚É’u‚­
	if (m_unit.GetLift() != nullptr)
	{
		m_unit.GetLift()->LiftEnd();
		m_unit.GetLift()->Position(MyVector3(m_unit.GetLift()->Position().x, 0.0f, m_unit.GetLift()->Position().z));
		//‰Šú‰»
		m_unit.Message((int)UnitMessageID::LIFT, nullptr);
		m_world.GetBillBoardManager().Find(BillBoardID::HAVE_UI, m_unit.PositionPtr())->Delete();
	}
}

void DeadNode::End()
{
}

bool DeadNode::Branch()
{
	return m_unit.IsDead();
}

void DeadNode::OnUpdate(float deltaTime)
{	
	//Œo˜H‚ğíœ
	m_unit.RoadDelete();
}

bool DeadNode::SetIsEnd()
{
	return false;
}
