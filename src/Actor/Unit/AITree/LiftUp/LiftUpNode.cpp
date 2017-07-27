#include "LiftUpNode.h"
#include"Actor\Unit\Unit.h"
#include"Actor\Parts\Parts.h"
#include"Actor\Influence\Enemy\VerdictConstant.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Base/UtilTemplate/UtilTemplate.h"
#include"World/World.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitAnimationID.h"
#include"../../Base/UnitMessageID.h"
LiftUpNode::LiftUpNode(IWorld & world, Unit& unit):
	UnitAINode(unit,UnitNodeID::LIFT_UP),
	m_world(world)
{
}

LiftUpNode::~LiftUpNode()
{
}

void LiftUpNode::Start()
{
	m_unit.GetModel().ChangeAnimation((int)UnitAnimationID::LIFT_UP, false);
	m_unit.GetModel().Update(0.0f, m_unit.GetPose());

	if (m_unit.GetLift()->GetID() == LIFT_ID::UNIT)//ユニットを持っている場合
		m_world.GetBillBoardManager().Create(BillBoardID::HAVE_UI, TEXTURE_ID::HAVE_UNIT, m_unit.PositionPtr(), MyVector3(0, 30, 0), 20.0f);
	else//資源を持っている場合
		m_world.GetBillBoardManager().Create(BillBoardID::HAVE_UI, TEXTURE_ID::HAVE_PARTS, m_unit.PositionPtr(), MyVector3(0, 30, 0), 20.0f);
	m_isEnd = false;
}
void LiftUpNode::End()
{
	m_unit.GetLift()->LiftUpEnd();
}

bool LiftUpNode::Branch()
{
	if (m_unit.GetLift() != nullptr)
	{
		return !m_unit.GetLift()->IsLiftEnd();
	}

	auto lift = m_world.GetGameManager().GetMetaAI().Distance().GetNearLift(m_unit);
	if (lift == nullptr ||lift->IsLiftStart()|| lift->IsDelete()) return false;

	if (m_world.GetGameManager().GetMetaAI().Distance().Distance(*lift,m_unit) <=
		m_world.GetGameManager().GetCSV().Get_F(CSV_DATA_ID::UNIT_LIFT_RANGE, 1))
	{
		m_unit.Message((int)UnitMessageID::LIFT, &lift);
		m_unit.GetLift()->LiftStart();
		return true;
	}
	return false;
}

void LiftUpNode::OnUpdate(float deltaTime)
{
	m_unit.Agent().Delete();
	MyVector3 v = m_unit.GetLift()->Position() - m_unit.Position();
	v.y = 0.0f;
	if(m_unit.RotateVelocity(v,deltaTime))
		m_unit.GetLift()->LiftUp(m_unit);//ユニットの持っている物体にユニット自体を渡す
}

bool LiftUpNode::SetIsEnd()
{
	return m_unit.GetModel().IsAnimationEnd();
}
